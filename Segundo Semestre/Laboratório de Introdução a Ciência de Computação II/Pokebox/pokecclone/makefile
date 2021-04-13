CC = gcc
TARGET = main.c
BINARY = main
INCLUDES = ./includes
SOURCES = ./sources

all:
	$(CC) -Wall -Werror $(TARGET) $(SOURCES)/*.c -g -o $(BINARY) -I $(INCLUDES)

clean:
	rm -r $(BINARY) ../pokecclone.zip

run:
	./$(BINARY)

valgrind:
	valgrind --leak-check=full ./$(BINARY)

zip:
	zip -r ../pokecclone.zip $(TARGET) $(INCLUDES) $(SOURCES) ./data makefile pokemon