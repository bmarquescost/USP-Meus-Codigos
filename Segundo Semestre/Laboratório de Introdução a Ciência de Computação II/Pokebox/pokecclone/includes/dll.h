#ifndef _DLL_H_
#define _DLL_H_

typedef struct _pokebox BOX;
typedef struct _pokelist POKELIST;

#include "PokeBox.h"
#include "SpriteManager.h"

#define INITIAL_BOX_AMOUNT 3

POKELIST *pokelist_create(void);
void pokelist_delete(POKELIST **);

void pokelist_print_box(POKELIST *);   // 5

void pokelist_right_pokebox(POKELIST *); // 1
void pokelist_left_pokebox(POKELIST *);  // -1

void pokelist_insert_box_at_end(POKELIST *); // 2
void pokelist_remove_box(POKELIST *); // -2

void pokelist_insert_pokemon_indexed(POKELIST *, pokemon_t *, int); // 4
void pokelist_insert_pokemon_current_box(POKELIST *, pokemon_t *);  // 3
void pokelist_remove_pokemon_indexed(POKELIST *, int);  // -4


#endif