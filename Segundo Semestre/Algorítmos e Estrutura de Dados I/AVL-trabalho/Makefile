# Arquivo Makefile para compilação e execução do programa
CC=gcc
LD=gcc

CFLAGS=-Wall -Wextra -Werror -pedantic -g -O0
LFLAGS=-lm -g

VFLAGS=--leak-check=full --show-leak-kinds=all --track-origins=yes

OBJS=main.o avl.o
TARGET=exec

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJS)
	@$(LD) $(LFLAGS) $(OBJS) -o $(TARGET)

clean:
	@rm -rf $(OBJS) $(TARGET)

run:
	@./$(TARGET)

valgrind: all
	@valgrind $(VFLAGS) ./$(TARGET)

zip:
	@zip -r trab.zip Makefile *.c *.h