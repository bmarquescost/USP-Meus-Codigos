/*
    ICMC - Instituto de Ciências Matemáticas e de Computação 
    LAB ICC II
    
    Professor: Leonardo Pereira
    Aluno: Bernardo Marques Costa
*/

#include <stdio.h>
#include <stdlib.h>

#include "PokeType.h"
#include "Pokemon.h"
#include "PokeDex.h"

#include "sorts.h"

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


int main() {

    char *algoritm_aux = readline(stdin); 
    int algoritm = atoi(algoritm_aux);
    free(algoritm_aux);

    char *field_compared = readline(stdin);

    char *pokemon_filename = readline(stdin);

    int totalPkmn = 0;
    pokemon_t **pokelist = readPkDex(&totalPkmn, pokemon_filename);
    
    pokelist_sort(pokelist, totalPkmn, algoritm, field_compared);
 
    free(field_compared);
    free(pokemon_filename);
    
    for(int i = 0; i < totalPkmn; ++i)    {
        printPokemon(pokelist[i]);
        free(pokelist[i]);
    }

    free(pokelist);

	return 0;
}

