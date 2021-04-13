SOURCE = ./Source/*.c
INCLUDES = ./Includes/
BINARY = algoritm
FLAGS = -Werror -Wall -g

all:
	@gcc $(SOURCE) ./main.c -o $(BINARY) -I $(INCLUDES) $(FLAGS)

# To run your program, use ./algoritm in the comand line

clean:
	@rm -rf *.dat $(BINARY)

zip:
	zip -r Algoritmos Makefile ./Source ./Data ./Includes ./main.c AnaliseAlgoritmo.pdf plot.py