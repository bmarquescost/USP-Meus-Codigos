SOURCE = ./item.c ./arvbinbusca.c
MAIN = ./main.c
BINARY = ./perf_balanceada
CFLAGS = -Wall -Werror -g
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full 
CC = gcc

all:
	@$(CC) $(MAIN) $(SOURCE) -o $(BINARY) $(CFLAGS)

run:
	@$(BINARY)

valgrind:
	@valgrind $(VFLAGS) $(BINARY)

zip:
	zip -r Abb_perfeitamente_balanceada $(SOURCE) $(MAIN) Makefile ./*h