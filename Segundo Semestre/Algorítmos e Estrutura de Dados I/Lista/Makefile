CC = gcc
FLAGS = -Wall -Werror -g
BINARY = ./lista
MAIN = ./main.c
INCLUDES = ./includes
SOURCE = ./source/item.c ./source/listaEncadeada.c

all:
	@$(CC) $(MAIN) $(SOURCE) -o $(BINARY) -I $(INCLUDES) $(FLAGS)

run:
	@$(BINARY)

zip:
	zip -v -r ListaEncadeada ./source $(INCLUDES) $(MAIN) Makefile

clear:
	@rm -rf $(BINARY)