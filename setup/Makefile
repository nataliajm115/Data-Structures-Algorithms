### Makefile for Data Structure and Algorihms. Do not modify this!

GCC = gcc -g -O2 -std=c99 -pedantic -Wall -Wno-unused-result -lm

DIFF = diff -w

.PHONY: default run

NAME = setup

default:
	@echo "Welcome to this DSA exercise!\n"
	@echo "Please edit the .c files to answer the question."
	@echo "Then use 'make run' to run and manually test your program."

run: setup
	./setup

## List of Executables

setup: setup.c
	$(GCC) $^ -o $@
