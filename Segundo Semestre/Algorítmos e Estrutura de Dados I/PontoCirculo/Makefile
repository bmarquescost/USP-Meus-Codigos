INCLUDES = ./includes
PROG = ./teste
MAIN = main.c
FLAGS = -Wall -Werror -g

all: compile

compile:
	@gcc $(MAIN) circulo.c ponto.c -I $(INCLUDES) -o $(PROG) $(FLAGS)

valgrind:
	@valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all $(PROG)

clean:
	@rm *.o $(PROG)

run:
	@$(PROG)

zip:
	zip -r Circulo.zip ./includes/*.h *.c Makefile