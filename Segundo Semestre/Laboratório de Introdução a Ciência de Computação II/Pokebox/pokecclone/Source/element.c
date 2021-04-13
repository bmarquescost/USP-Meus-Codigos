#include <stdio.h>
#include <stdlib.h>

#include "element.h"

struct _element {
    pokemon_t **pokebox;
    int num_pokemon;
};

ELEMENT *element_create(void) {
    ELEMENT *new_pokebox = calloc(1,sizeof(ELEMENT));
    new_pokebox->pokebox = calloc(BOXSIZE, sizeof(pokemon_t*));
    return new_pokebox;
}

/* Delete element that contains box of pokemons (memory will be free'ed in other .c program) */
void element_destruct(ELEMENT *element) {
    if(element != NULL) {
        for(int i = 0; i < BOXSIZE; ++i)
            element->pokebox[i] = NULL;
        
        free(element->pokebox);
        free(element);
    }
}

/* Return index of one empty slot after a given initial index */
int element_find_empty_slot(ELEMENT *element, int index) {
    for(int i = index; i < BOXSIZE; ++i){
        if(element->pokebox[i] == NULL)
            return i;
    }
    return -1;
}

/* Try to insert a pokemon in the box, return True (1) if it worked, 0 if the box is full */
int element_insert_pokemon_at_index(ELEMENT *element, pokemon_t *new_pokemon, int index) {
    if(element == NULL || new_pokemon == NULL) return 0;

    int possible_index = element_find_empty_slot(element, index);
    
    if(possible_index != -1) {
        element->pokebox[possible_index] = new_pokemon;
        return 1;
    }
    return 0;
}

/* Remove the reference to a pokemon in a pokebox slot based on index */
void element_remove_pokemon_at_index(ELEMENT *element, int index) {
    if(element == NULL) return;
    
    element->pokebox[index] = NULL; // memory will be free'ed later on
}

void element_print(ELEMENT *element) {
    if(element == NULL) return;

    printBox(element->pokebox);
}
