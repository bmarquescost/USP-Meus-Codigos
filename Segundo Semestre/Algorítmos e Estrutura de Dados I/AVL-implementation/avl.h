#ifndef _AVL_H_
#define _AVL_H_

typedef struct _node Node;
typedef struct _avl Avl;
typedef int ITEM;

Avl *avl_create(void);
void avl_destruct(Avl **avl_tree);
void avl_insert(Avl *avl_tree, int key);
void avl_remove(Avl *avl_tree, int key);
void avl_print(Avl *tree);


#endif