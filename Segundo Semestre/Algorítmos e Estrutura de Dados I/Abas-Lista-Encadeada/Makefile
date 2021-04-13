CFLAGS = -Wall -Werror -g 
VFLAGS = --show-leak-kinds=all --track-origins=yes --leak-check=full
CC = gcc
BINARY = ./tab
MAIN = ./main.c
SOURCE = ./source
INCLUDE = ./include

all: compile

compile:
	@$(CC) $(MAIN) $(SOURCE)/*.c -o $(BINARY) -I $(INCLUDE) $(CFLAGS)

run:
	@$(BINARY)

valgrind:
	@valgrind $(VFLAGS) $(BINARY)
zip:
	zip -rv Tabs-ALGI $(MAIN) $(SOURCE) $(INCLUDE) Makefile