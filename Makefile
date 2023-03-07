CC := riscv64-unknown-elf-gcc
AR := riscv64-unknown-elf-ar
LIB := libdummylibc.a

default: fmt

fmt:
	clang-format -i -style=Google $(wildcard *.h */*.h *.c */*.c libc/*.h libc/src/*.c)
	git diff --exit-code

$(LIB): impl.o
	$(AR) rcs $@ $^

impl.o: libc/src/impl.c
	$(CC) -O3 -g -c $< -o $@ -I libc -D__SHARED_LIBRARY__

clean:
	rm -rf $(LIB) impl.o

.PHONY: clean default fmt
