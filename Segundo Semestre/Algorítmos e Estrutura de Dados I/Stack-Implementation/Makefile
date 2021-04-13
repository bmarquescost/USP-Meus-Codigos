INCLUDES = ./includes/
SOURCE = ./source/
PROG = main.c
BINARY = ./palindromo
FLAGS = -g -Wall -Werror

all: compile

compile:
	@gcc $(SOURCE)/*.c  $(PROG) -o $(BINARY) -I $(INCLUDES) $(FLAGS)

run:
	@$(BINARY)

zip:
	zip -r Palindromo $(INCLUDES) Makefile $(SOURCE) $(PROG)

valgrind:
	@valgrind --show-leak-kinds=all --track-origins-yes --leak-check=full $(BINARY)
