MAIN = Main.c
SOURCE = *.a sorts.c
BINARY = ./sort_poke
CC = gcc
CFLAGS = -Wall -Werror -g
VFLAGS = --show-leak-kinds=all --leak-check=full --track-origins=yes

all: 
	@$(CC) $(MAIN) $(SOURCE) -o $(BINARY) $(CFLAGS)

run:
	@$(BINARY) 

valgrind: 
	valgrind $(VFLAGS) $(BINARY)

zip:
	zip -r -v Sort_Pokedex *.c *.a *.h Main.c Makefile Relatorio-6-Pokemons-Sort.pdf