#ifndef _ELEMENT_H_
    #define _ELEMENT_H_
    
    #define TRUE 1
    #define FALSE 0
    #define boolean int

    typedef struct _element ELEMENT;

    ELEMENT *element_create(int key);
    boolean element_delete(ELEMENT **item);
    void element_print(ELEMENT *item);
    int element_get_key(ELEMENT *item);
    boolean element_set_key(ELEMENT *item, int newKey);

#endif 