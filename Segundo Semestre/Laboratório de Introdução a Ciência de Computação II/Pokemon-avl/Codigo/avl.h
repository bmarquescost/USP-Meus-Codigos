#ifndef _AVL_H_
#define _AVL_H_

typedef struct _avl AVL;
typedef struct _node NODE;

AVL *avl_create(void);
void avl_delete(AVL **tree);
int avl_height(NODE *root);
void avl_insert_pokemon(AVL *tree, pokemon_t *pokemon);
void avl_print_pre_order(AVL *poketree);
void avl_print_in_order(AVL *poketree);
void avl_print_pos_order(AVL *poketree);

#endif