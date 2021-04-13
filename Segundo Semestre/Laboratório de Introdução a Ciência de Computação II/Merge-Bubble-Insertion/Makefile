INCLUDE = ./include
SOURCE = ./source/filemanager.c ./source/sortalgoritm.c 
CFLAGS = -Wall -Werror -g 
VFLAGS = --track-origins=yes --show-leak-kinds=all --leak-check=full
DEBUGFLAGS = -fsanitize=address
CC = gcc
BINARY = ./sort
MAIN = ./main.c

all:
	@$(CC) $(MAIN) $(SOURCE) -o $(BINARY) -I $(INCLUDE) $(CFLAGS)

valgrind:
	@valgrind $(VFLAGS) $(BINARY)

debug: 
	@$(CC) -DDEBUG $(MAIN) $(SOURCE) -o $(BINARY) -I $(INCLUDE) $(CFLAGS) 

run:
	$(BINARY)

address_debug:
	@$(CC) $(MAIN) $(SOURCE) -o $(BINARY) -I $(INCLUDE) $(CFLAGS) $(DEBUGFLAGS)

clean:
	@rm -r *.dat $(BINARY)

zip:
	zip -r -v SortAlgoritm $(MAIN) ./source $(INCLUDE) Makefile plot.py Relatorio
