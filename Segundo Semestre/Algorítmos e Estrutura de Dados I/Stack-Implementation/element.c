// Bernardo Marques Costa
#include <stdio.h>
#include <stdlib.h>

#include "element.h"

struct _element {
    int key;
};

// Create the element with it key parameter
ELEMENT *element_create(int key) {
    ELEMENT *item;
    item = (ELEMENT *) malloc(sizeof(ELEMENT));
    
    if (item)
        item->key = key;
         
    return item;
}

// Delete an instance element.
boolean element_delete(ELEMENT **item) {
    if (!item)
        return FALSE;

    free(*item);
    *item = NULL;

    return TRUE;
}

// Print an item key value.
void element_print(ELEMENT *item) {
    if (item)
        printf("%d\n", item->key);
    else
        printf("Item não existe");
}

// Return the value of the key argument.
int element_get_key(ELEMENT *item) {
    if (item)
        return item->key;
    
    exit(1);
}

// Set the new value of an item key. 
boolean element_set_key(ELEMENT *item, int newKey) {
    if (!item)
        return FALSE;

    item->key = newKey;
    return TRUE;
}