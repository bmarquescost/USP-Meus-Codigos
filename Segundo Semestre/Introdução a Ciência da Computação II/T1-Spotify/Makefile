CFLAGS = -Wall -Werror -g
VFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
CC = gcc
MAIN = main.c
BINARY = ./spotify
SOURCE = ./source
INCLUDES = ./includes

all:
	@$(CC) $(MAIN) $(SOURCE)/*.c -o $(BINARY) -I $(INCLUDES) $(CFLAGS)

run:
	@$(BINARY)

valgrind:
	@valgrind $(VFLAGS) $(BINARY)

zip:
	zip -r Spotify-Trabalho-1 $(MAIN) $(SOURCE) $(INCLUDES) Makefile