#include <stdio.h>
#include <stdlib.h>

#include "avl.h"


int main(int argc, char *argv[]) {
    Avl *tree = avl_create();

    avl_insert(tree, 10);
    avl_print(tree); 
    avl_insert(tree, 5);
    avl_print(tree);
    avl_insert(tree, 15);
    avl_print(tree);
    avl_insert(tree, 3);
    avl_print(tree);
    avl_insert(tree, 2);
    avl_print(tree);
    avl_insert(tree, 12);
    avl_insert(tree, 13);
    avl_insert(tree, 14);
    avl_print(tree);

    
    avl_remove(tree, 13);
    avl_print(tree);
    avl_remove(tree, 10);
    avl_remove(tree, 14);    

    
    avl_print(tree);
    avl_destruct(&tree);
    
    return 0;
}
