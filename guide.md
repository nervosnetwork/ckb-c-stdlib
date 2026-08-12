# CKB C Standard Library — Developer Guide
This is a C runtime library for on-chain scripts (smart contracts) on CKB. It provides a partial implementation of the standard C runtime.

This guide is for AI agents to scaffold a new project from scratch. It is also helpful when projects are not correctly configured.

Clang is the recommended compiler, version 19 or later.

It should include a Makefile under project root. specify variable `CC` and `LD`.

The `ckb-c-stdlib` should be referenced as a git submodule at the location `deps/ckb-c-stdlib` with the URL https://github.com/nervosnetwork/ckb-c-stdlib.git.

The following compilation options(CFLAGS) should be used:
<compiler_options>
--target=riscv64 -march=rv64imc_zba_zbb_zbc_zbs
-O3
-fdata-sections -ffunction-sections
-fno-builtin-printf -fno-builtin-memcmp
-nostdlib
</compiler_options>

Users can add their own options. It is not necessary to add the `-g` option. Don't use `-fPIE`.


The following linker options(LDFLAGS) should be used:
<linker_option>
`-static --gc-sections`
</linker_option>

When clang is used as the linker driver (the single compilation unit method below), linker-only flags must be passed with a `-Wl,` prefix, e.g. `-Wl,--gc-sections`. A bare `--gc-sections` is rejected by clang with `error: unknown argument`.

Keep the final binary small; debug information is not needed. Warn users if the final binary size exceeds 400K.

Every project should have a reproducible build. Use [this script](https://github.com/nervosnetwork/ckb-script-templates/blob/main/workspace/scripts/reproducible_build_docker). Put it here: `script/reproducible_build_docker`.

The final binary output directory is `./build`. Place source files under `./c` unless users explicitly request other locations. Create the `build`  directory if it is missing.

Add the macro `CKB_PRINTF_DECLARATION_ONLY` when any of the `printf` or `sprintf` family of functions is used. Don't forget to include `ckb_syscalls.h`, since printf use `ckb_debug` syscall.

To actually enable `printf`/`ckb_printf` (instead of them being compiled as empty stubs that silently return 0), the macro `CKB_C_STDLIB_PRINTF` must also be defined, e.g. `-DCKB_C_STDLIB_PRINTF`.

The `malloc` and `free` functions are not implemented, so they should not be used. If users provide their own, follow the instructions for using them.

## Compilation Method
By default, ckb-c-stdlib uses a single big header file strategy, suitable for a single C compilation unit. A minimal `c/main.c` that prints `hello, world`:

```c
#include "ckb_syscalls.h"
#include <stdio.h>

int main(void) {
  printf("hello, world\n");
  return 0;
}
```

A complete Makefile:
```
CC := clang
LD := ld.lld

CFLAGS := --target=riscv64 -march=rv64imc_zba_zbb_zbc_zbs -O3 \
          -fdata-sections -ffunction-sections \
          -fno-builtin-printf -fno-builtin-memcmp \
          -nostdlib \
          -DCKB_C_STDLIB_PRINTF -DCKB_PRINTF_DECLARATION_ONLY \
          -Ideps/ckb-c-stdlib -Ideps/ckb-c-stdlib/libc
LDFLAGS := -static -Wl,--gc-sections

CHECKSUM_FILE ?= checksums.txt

default: build

build: build/main

build/main: c/main.c
    mkdir -p build
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

checksum: build
	shasum -a 256 build/* > $(CHECKSUM_FILE)

clean:
	rm -rf build

.PHONY: default build checksum clean
```
Notes:
- The `build`, `checksum` and `clean` targets are required by `./scripts/reproducible_build_docker`, which runs `make build` for verification and `make clean checksum CHECKSUM_FILE=checksums.txt` for `--update`.
- The include paths: `ckb_syscalls.h` lives in `deps/ckb-c-stdlib`, while `stdio.h`/`entry.h` live in `deps/ckb-c-stdlib/libc`.


It also supports multiple compilation units with the following settings. When compiling C files, add the macro `CKB_DECLARATION_ONLY`. Compile `libc/src/impl.c` without this macro. Finally, link all objects (including impl.o) together with `ld`:
```
$(LD) $(LDFLAGS) -o $@ $^
```

## Tests
It should compile the target project successfully on a local machine. Warn users if clang is not
used or the version does not meet the requirement.

It should be built with a reproducible build when docker is available. Verify as follows:
- Docker check (if available): run the locked build via `./scripts/reproducible_build_docker` and confirm `build/*` matches `checksums.txt`.
- Keep a `checksums.txt` in the repo; regenerate it with `reproducible_build_docker --update`
  whenever the binary intentionally changes, and fail the test if it doesn't match.

If Docker is not available, warn users and skip the reproducible build step.

Note that the locally installed clang may produce a binary that is not byte-identical to the
locked docker build. This is expected: only the docker build is required to match `checksums.txt`, the
local build only needs to compile successfully. 

## CKB Syscalls
When using CKB syscalls, refer to the following documents for usage instructions:
- https://github.com/nervosnetwork/rfcs/blob/master/rfcs/0009-vm-syscalls/0009-vm-syscalls.md
- https://github.com/nervosnetwork/rfcs/blob/master/rfcs/0034-vm-syscalls-2/0034-vm-syscalls-2.md
- https://github.com/nervosnetwork/rfcs/blob/master/rfcs/0050-vm-syscalls-3/0050-vm-syscalls-3.md
