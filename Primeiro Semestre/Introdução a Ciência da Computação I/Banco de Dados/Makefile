PROG = ./sgbd
FLAGS = -Wall -Werror -g

all: compile

compile:
	@gcc main.c SuportSGBD.c -o $(PROG) $(FLAGS)

valgrind:
	@valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all $(PROG)

clean: 
	@rm -r *.idx *.reg ./sgbd *.o

run:
	@$(PROG)

zip:
	zip -r SGBD.zip *.c *.h Makefile