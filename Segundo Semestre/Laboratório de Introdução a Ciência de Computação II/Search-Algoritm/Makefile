PROG = main.c
BINARY = ./search
SOURCE = ./Source
INCLUDES = ./Includes
CC = gcc
CFLAGS = -Wall -Werror -g

all:
	@$(CC) $(PROG) $(SOURCE)/*.c -I $(INCLUDES) -o $(BINARY) $(CFLAGS)

run:
	@$(BINARY)

clear:
	@rm $(BINARY)

zip:
	@zip -r SearchAlgoritm $(SOURCE) Makefile $(INCLUDES) $(PROG) AnáliseBuscas.pdf 
