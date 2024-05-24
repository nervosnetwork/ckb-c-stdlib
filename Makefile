CC := riscv64-unknown-elf-gcc
AR := riscv64-unknown-elf-ar
LIB := libdummylibc.a
CFLAGS := -Wall -Werror -Wextra -Wno-unused-parameter -Wno-dangling-pointer -Wno-nonnull -Wno-nonnull-compare -fno-builtin-printf -fno-builtin-memcmp -O3 -g -fdata-sections -ffunction-sections

LDFLAGS := -nostdlib -nostartfiles -Wl,-static -Wl,--gc-sections
EXTRA := -I . -I libc -I molecule -Wno-unused-function -Wno-array-bounds -Wno-stringop-overflow

# nervos/ckb-riscv-gnu-toolchain:jammy-20230214
BUILDER_DOCKER := nervos/ckb-riscv-gnu-toolchain@sha256:d175f4a766b4b17a44bd9bbeca8e24ab2427ba615738016dc49e194046e6b28b
CLANG_FORMAT_DOCKER := xujiandong/ckb-riscv-llvm-toolchain@sha256:6409ab0d3e335c74088b54f4f73252f4b3367ae364d5c7ca7acee82135f5af4d


default: fmt

all-via-docker:
	docker run -u $(shell id -u):$(shell id -g) --rm -v `pwd`:/code ${BUILDER_DOCKER} bash -c "cd /code && make all"

all: tests/ci

tests/ci: tests/ci.c
	$(CC) $(CFLAGS) $(EXTRA) $(LDFLAGS) -o $@ $<

ALL_C_SOURCE := $(wildcard *.h */*.h *.c */*.c libc/*.h libc/src/*.c)

fmt:
	docker run -u $(shell id -u):$(shell id -g) --rm -v `pwd`:/code ${CLANG_FORMAT_DOCKER} bash -c "cd code && clang-format -i -style='{BasedOnStyle: google, SortIncludes: false}' $(ALL_C_SOURCE)"
	git diff --exit-code $(ALL_C_SOURCE)


$(LIB): impl.o
	$(AR) rcs $@ $^

impl.o: libc/src/impl.c
	$(CC) $(CFLAGS) -c $< -o $@ -I libc -D__SHARED_LIBRARY__

clean:
	rm -rf $(LIB) impl.o
	rm tests/ci

.PHONY: clean default fmt
