CC = gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -g -O0 -std=c99
VFLAGS = --track-origins=yes --show-leak-kinds=all --leak-check=full
BINARY = ./menu
MAIN = ./main.c
SOURCE = ./source/*.c
INCLUDE = ./include

all: compile

compile: 
	@$(CC) $(MAIN) $(SOURCE) -o $(BINARY) -I $(INCLUDE) $(CFLAG)

valgrind: 
	@valgrind $(VFLAGS) $(BINARY)

run:
	@$(BINARY)

zip:
	zip -r Minigooglebot ./source $(INCLUDE) $(MAIN) Makefile README.md googlebot.txt
