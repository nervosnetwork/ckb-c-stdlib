fmt:
	clang-format -i -style=Google $(wildcard *.h */*.h *.c */*.c libc/*.h libc/src/*.c)
	git diff --exit-code

.PHONY: fmt
