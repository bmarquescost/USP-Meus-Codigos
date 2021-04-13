SOURCE = *.a avl.c
MAIN = Main.c
BINARY = ./poketree
CFLAGS = -Wall -Werror -g
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full 
CC = gcc 

all:
	@$(CC) $(MAIN) $(SOURCE) -o $(BINARY) $(CFLAGS)

run:
	@$(BINARY)

valgrind:
	valgrind $(VFLAGS) $(BINARY)

zip:
	zip -r -v PokeTree $(MAIN) $(SOURCE) Makefile *.h
