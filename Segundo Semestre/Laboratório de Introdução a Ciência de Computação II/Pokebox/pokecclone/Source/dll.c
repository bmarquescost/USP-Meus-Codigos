#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "element.h"
#include "dll.h"

struct _pokebox {
    ELEMENT *element; 
    BOX *previous;
    BOX *next;
};

struct _pokelist {
    BOX *head;
    BOX *current_box;
    int num_boxes;
};

/* Insert a new node (pokebox), at the end of the list */
void pokelist_insert_box_at_end(POKELIST *pl) {
    assert(pl != NULL);

    BOX *new_box = calloc(1,sizeof(BOX));

    new_box->element = element_create();

    /* Insert node on an empty pokelist */
    if(pl->head == NULL) {
        pl->head = new_box;
        new_box->next = new_box;
        new_box->previous = new_box;
        pl->current_box = new_box;
    }
    /* Insert node on a non empty pokelist */
    else {
        new_box->next = pl->head;
        pl->current_box->next = new_box;
        new_box->previous = pl->current_box;
        pl->current_box = new_box;
    }
}

/* Filling with 3 nodes of pokemon boxes */
static void _initial_boxes(POKELIST *pl) {
    assert(pl != NULL);

    for(int i = 0; i < INITIAL_BOX_AMOUNT; ++i) { 
        pokelist_insert_box_at_end(pl);        
        ++pl->num_boxes;
    }
}

/* Create a new pokemon list, adding the 3 initial empty pokeboxes */
POKELIST *pokelist_create(void) {
    POKELIST *new_pokelist = calloc(1,sizeof(POKELIST));    
    
    _initial_boxes(new_pokelist);

    return new_pokelist;
}

/* Delete all pokelist, freeing all nodes */
void pokelist_delete(POKELIST **pl) {
    assert(*pl != NULL && (*pl)->head != NULL);
    
    BOX *current_node = (*pl)->head->next;

    while(current_node != (*pl)->head) {
        BOX *deleted_node = current_node;
        current_node = current_node->next;

        element_destruct(deleted_node->element);
        
        free(deleted_node);
        deleted_node = NULL;
    }

    /* Freeing head node of the list */
    element_destruct((*pl)->head->element);
    free((*pl)->head);
    (*pl)->head = NULL;

    free(*pl);
    *pl = NULL;
}

/* Print current pokebox */
void pokelist_print_box(POKELIST *pl) {
    assert(pl != NULL);

    element_print(pl->current_box->element);
}

/* Set curretn node to the right (previous) */
void pokelist_right_pokebox(POKELIST *pl) {
    assert(pl != NULL);
    pl->current_box = pl->current_box->next;
} 

/* Set current node to the left (previous) */
void pokelist_left_pokebox(POKELIST *pl) {
    assert(pl != NULL);
    pl->current_box = pl->current_box->previous;
}

/* Remove current box from pokelist */
void pokelist_remove_box(POKELIST *pl) {
    assert(pl != NULL && pl->num_boxes != 0);

    BOX *will_be_deleted = pl->current_box;
    
    if(will_be_deleted == pl->head)
        pl->head = pl->head->next;

    will_be_deleted->next->previous = will_be_deleted->previous; // next node will have reference to the previous one
    will_be_deleted->previous->next = will_be_deleted->next; // previous node will have reference to the next one
    pl->current_box = will_be_deleted->next; // current node will be the one after the deleted node

    --pl->num_boxes;
    element_destruct(will_be_deleted->element);
    free(will_be_deleted);
}

static void _insert_pokemon_in_index(POKELIST *pl, pokemon_t *new_pokemon, int index) {

    /* Insert into a empty slot in current box */
    int insertion_succeed = element_insert_pokemon_at_index(pl->current_box->element, new_pokemon, index);
    if(insertion_succeed)
        return; 

    else {
        /* If it doesn't return yet, current box does not have empty slot after chosen index */
        /* We will loop trough list, untill we come back to the head node */
        if(pl->current_box->next != NULL) {
            
            BOX *current_box = pl->current_box->next;

            while(current_box != pl->head) {
                insertion_succeed = element_insert_pokemon_at_index(current_box->element, new_pokemon, index);
                if(insertion_succeed)
                    return; 
                current_box = current_box->next;
            } 
        }

        /* Else: we need to create a new box at the end of the list, and then insert new pokemon in the first index */
        pokelist_insert_box_at_end(pl);
        element_insert_pokemon_at_index(pl->current_box->element, new_pokemon, 0);
    }
}   

/* Insert pokemon in current box given an index */
void pokelist_insert_pokemon_indexed(POKELIST *pl, pokemon_t *new_pokemon, int index) {
    assert(pl != NULL && new_pokemon != NULL);
    
    _insert_pokemon_in_index(pl, new_pokemon, index);
}

/* Insert pokemon in current box in first index */
void pokelist_insert_pokemon_current_box(POKELIST *pl, pokemon_t * new_pokemon) {
    assert(pl != NULL && new_pokemon != NULL);

    _insert_pokemon_in_index(pl, new_pokemon, 0);
}

/* Destroy a reference in current pokebox to one pokemon, based on index */
void pokelist_remove_pokemon_indexed(POKELIST *pl, int index) {
    assert(pl != NULL);
    element_remove_pokemon_at_index(pl->current_box->element, index); 
}