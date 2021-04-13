CC = gcc
SOURCE = ./source/*.c
INCLUDE = ./includes
BINARY = ./spellchecker
MAIN = main.c
CFLAGS = -Wall -Werror -g
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full

all: compile

run:
	@$(BINARY)


compile:
	@$(CC) $(MAIN) $(SOURCE) -o $(BINARY) -I $(INCLUDE) $(CFLAGS)

valgrind:
	@valgrind $(VFLAGS) $(BINARY)

zip:
	zip -rv Spellchecker $(MAIN) ./source $(INCLUDE) Makefile