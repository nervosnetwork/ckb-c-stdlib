fmt:
	clang-format -i -style=Google $(wildcard *.h */*.h *.c */*.c libc/include/*.h libc/src/*.c)
	git diff --exit-code

.PHONY: fmt
