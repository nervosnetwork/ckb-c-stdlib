fmt:
	clang-format -i -style=Google $(wildcard *.h */*.h *.c */*.c)
	git diff --exit-code

.PHONY: fmt
