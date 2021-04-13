#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include "PokeBox.h"

typedef struct _element ELEMENT;

ELEMENT *element_create(void);
void element_destruct(ELEMENT *);
int element_find_empty_slot(ELEMENT *, int);
int element_insert_pokemon_at_index(ELEMENT *, pokemon_t *, int);
void element_remove_pokemon_at_index(ELEMENT *, int);
void element_print(ELEMENT *);

#endif