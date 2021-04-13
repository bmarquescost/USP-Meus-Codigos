/*
    Aluno: Bernardo Marques Costa
    Número USP: 11795551
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "tab.h"

struct _node {
    TAB_DATA *tab;
    NODE *next;
};

struct _list {
    NODE *head;
    NODE *tail;
    int num_nodes;
};

// Constructor of a list
LIST *list_create(){
    LIST *l = calloc(1,sizeof(LIST));
    l->head = NULL;
    l->tail = NULL;
    l->num_nodes = 0;

    return l;
}

// Node destructor
void _delete_node(NODE *node){
    if(node == NULL) return;
    tab_delete(&node->tab);
    node->tab = NULL;

    free(node);
    node = NULL;
}

// Destructor: delete all list and it's data
boolean list_delete(LIST **l){
    if(l == NULL) return FALSE;
    if(*l == NULL) return FALSE;
     
    NODE *tmp = (*l)->head;

    while(tmp != NULL){
        (*l)->head = tmp->next;
        
        _delete_node(tmp);

        tmp = (*l)->head;
    }
    free(*l);
    return TRUE;
}

// Add an new node with tab data at the end of the list
boolean list_push(LIST *l, TAB_DATA *tab){
    if(l == NULL || tab == NULL) return FALSE;
    
    NODE *new_node = calloc(1,sizeof(NODE));
    new_node->tab = tab;
    new_node->next = NULL;
    
    if(l->head == NULL){ 
        l->head = new_node;
        l->tail = new_node;
    }  

    else{
        l->tail->next = new_node;
        l->tail = new_node;
    }

    l->num_nodes++;
    
    return TRUE;
}

// Pop from the list the node that contains a tab with the given title
NODE *list_pop(LIST *l, char *title){
    if(list_check_existence(l, title) == FALSE) return NULL;
    
    NODE *previous = NULL;
    NODE *current = l->head;

    // Since we have guaranteed that the list have at least one element with this title
    // we can break the loop with strcasecmp, finding the position of the node that contains
    // the title.
    while(1){
        if(strcasecmp(tab_get_title(current->tab), title) == 0)
            break;
        previous = current;        
        current = current->next;
    }

    if(current == l->head)
        l->head = current->next;

    else if(current->next == NULL){
        l->tail = previous;
        previous->next = NULL;
    }

    else
        previous->next = current->next;
    
    current->next = NULL;
    
    return current;
}


boolean list_change_pos(LIST *l, char *title, int index){
    if(l == NULL || title == NULL || index < 1)
        return FALSE;

    // List does not have an element with this title
    if(!list_check_existence(l,title))
        return FALSE;
    
    NODE *current = l->head;
    int count = 1;
    
    // Since exist at least one element with this title
    while(1){
        char *current_title = tab_get_title(current->tab);
        if(strcasecmp(current_title, title) == 0)
            break;
        current = current->next;
        ++count;
    }
    
    // Same index: we don't have to change tab at all
    if(count == index)
        return FALSE;
    
    NODE *changed_node = list_pop(l, title);
    
    // If we want to add the node at the start of the list
    if(index == 1){
        changed_node->next = l->head;
        l->head = changed_node;
        return TRUE;
    }

    // If we want to add the node at the end of the list
    else if(index >= l->num_nodes){
        l->tail->next = changed_node;
        l->tail = changed_node;
        return TRUE;
    }

    // If we want to add the want node somewhere else in the list (not start nor end)
    current = l->head;
    NODE *previous = NULL;

    for(int i = 1; i < index; ++i){
        previous = current;
        current = current->next;
    }
    
    previous->next = changed_node;
    changed_node->next = current;

    return TRUE;
}

// Check if a list has an node that contains an tab element with a given title
boolean list_check_existence(LIST *l, char *title){
    if(l == NULL || title == NULL) return FALSE;
    
    NODE *aux = l->head;
   
    while(aux != NULL){
        char *node_title = tab_get_title(aux->tab);
        if(strcasecmp(node_title, title) == 0)
            return TRUE;
        aux = aux->next;
    }

    return FALSE;
}

// Find a tab in the list with a given title
TAB_DATA *list_find(LIST *l, char *title){
    if(l == NULL || title == NULL) return NULL; 
    NODE *tmp = l->head;
    
    while(tmp != NULL){
        char *tmp_title = tab_get_title(tmp->tab);
        if(!strcasecmp(tmp_title, title))
            return tmp->tab;
        tmp = tmp->next;
    }
    return NULL;
}

int list_size(LIST *l){
    if(l == NULL) return ERROR;
    return l->num_nodes;
}

boolean list_empy(LIST *l){
    if(l == NULL) return FALSE;
    return l->num_nodes == 0;
}

boolean list_full(LIST *l){
    return FALSE; // Dinamic alocatade list never get full.
}

// Print all elements and nodes of the list
void list_print(LIST *l){
    if(l == NULL)
        return;
    
    NODE *aux = l->head;
    
    while(aux != NULL){
        tab_print(aux->tab);
        aux = aux->next;
    }
}
