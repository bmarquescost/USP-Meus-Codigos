/*
    ICMC - Instituto de Ciências Matemáticas e de Computação 
    LAB ICC II
    
    Professor: Leonardo Pereira
    Aluno: Bernardo Marques Costa
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "PokeType.h"
#include "Pokemon.h"
#include "PokeDex.h"

#include "avl.h"

// Função auxiliar para leitura de linha
char *readline(FILE *stream) {
    char character, *string = NULL;
    int pos = 0;
    do {
        string = realloc(string, pos+1);
        character = (int) fgetc(stream);
        
        if(character != '\r') {
            string[pos] = character;
            ++pos;
        }   

    } while(character != '\n' && !feof(stream));
    string[pos - 1] = '\0';

    return string;
}

int main()
{
    char *print_format_tmp = readline(stdin);
    int print_format = atoi(print_format_tmp);
    free(print_format_tmp);

    char *filename = readline(stdin);

    int num_pokemons = 0;
    pokemon_t **pokelist = readPkDex(&num_pokemons, filename);
    
    AVL *poketree = avl_create();
    for(int i = 0; i < num_pokemons; ++i)
        avl_insert_pokemon(poketree, pokelist[i]);     

    if(print_format == 1) 
        avl_print_pre_order(poketree);
    else if(print_format == 2)
        avl_print_in_order(poketree);
    else if(print_format == 3)
        avl_print_pos_order(poketree);

    // Liberando a memoria utilizada pelo programa
    for(int i = 0; i < num_pokemons; ++i)
        free(pokelist[i]);
    free(pokelist);

    avl_delete(&poketree);
    free(filename);
    
	return 0;
}
