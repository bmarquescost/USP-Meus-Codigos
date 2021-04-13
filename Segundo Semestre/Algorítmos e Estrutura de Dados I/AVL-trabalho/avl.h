#ifndef _AVL_H_
#define _AVL_H_

#include "boolean.h"

typedef struct avl * AVL;

AVL avl_create();
void avl_delete(AVL);

void avl_insert(AVL, int);
void avl_remove(AVL, int);
bool avl_search(AVL, int);

void avl_print_pre_order(AVL);
void avl_print_in_order(AVL);
void avl_print_pos_order(AVL);

#endif