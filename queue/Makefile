### Makefile for Data Structure and Algorihms. Do not modify this!

GCC = gcc -g -O2 -std=c99 -pedantic -Wall -Wno-unused-result -lm

DIFF = diff -w

VALGRIND = valgrind -s --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all --error-exitcode=111

.PHONY: default run-% test-% debug-% clean

NAME = queue

default:
	@echo "Welcome to the DSA exercise \"$(NAME)\"!\n"
	@echo "Please edit the $(NAME).c file to answer the question."
	@echo "Then use 'make run' to run and manually test your program."
	@echo "If it seems good, use 'make test' to run automated tests."
	@echo "To debug any memory problems, use 'make debug'."

run: $(NAME)
	./$(NAME)

TESTS := $(wildcard tests/*.input.txt)

.PHONY: run test $(TESTS)

test: $(TESTS)

$(TESTS): tests/%.input.txt: $(NAME)
	@echo -n "\nRunning test "
	@echo $*
	@(./$(NAME) < tests/$*.input.txt | $(DIFF) - tests/$*.output.txt && echo "\e[1;32mPASSED :-)\e[0m" ) || make --no-print-directory fail

debug: $(NAME)
	$(VALGRIND) ./$(NAME)

debug-test-1: $(NAME)
	cat tests/1.input.txt | $(VALGRIND) ./$(NAME)

fail:
	@echo "\e[1;31mFAILED :-( \e[0m"
	@echo "Please read the difference above carefully."
	@echo "< is what your program outputs"
	@echo "> is what the output should have been"
	@false

## List of Exercises

$(NAME): $(NAME).c libs/*.c
	$(GCC) $^ -o $@

clean:
	rm -f *.out *.a
