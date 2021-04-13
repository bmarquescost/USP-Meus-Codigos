CFLAGS = -Wall -Werror -g
VFLAGS = --leak-check=full --track-origins=yes --show-leak-kinds=all
CC = gcc
MAIN = main.c
BINARY = ./qtd_nos
SOURCE = arvorebinaria.c

all:
	@$(CC) $(MAIN) $(SOURCE) -o $(BINARY) $(CFLAGS)

run:
	@$(BINARY)

valgrind:
	@valgrind $(VFLAGS) $(BINARY)

zip:
	zip -v Arvore_nos $(SOURCE) arvorebinaria.h $(MAIN) Makefile