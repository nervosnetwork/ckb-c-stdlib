CC := riscv64-unknown-elf-gcc
AR := riscv64-unknown-elf-ar
LIB := libdummylibc.a
CFLAGS := -Wall -Werror -Wextra -Wno-unused-parameter -Wno-dangling-pointer -Wno-nonnull -Wno-nonnull-compare -fno-builtin-printf -fno-builtin-memcmp -O3 -g -fdata-sections -ffunction-sections

default: fmt

fmt:
	clang-format -i -style=Google $(wildcard *.h */*.h *.c */*.c libc/*.h libc/src/*.c)
	git diff --exit-code

$(LIB): impl.o
	$(AR) rcs $@ $^

impl.o: libc/src/impl.c
	$(CC) $(CFLAGS) -c $< -o $@ -I libc -D__SHARED_LIBRARY__

clean:
	rm -rf $(LIB) impl.o

.PHONY: clean default fmt
