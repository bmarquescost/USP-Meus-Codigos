/*
    Aluno: Bernardo Marques Costa
    Número USP: 11795551
*/
#include <stdio.h>
#include <stdlib.h>

#include "tab.h"


struct _tab {
    char *url;
    char *title;
};

// Tab constructor
TAB_DATA *tab_create(){
    
    TAB_DATA *new_tab = calloc(1,sizeof(TAB_DATA));
    
    new_tab->url = NULL;
    new_tab->title = NULL;

    return new_tab;
}

// Tab destructor
boolean tab_delete(TAB_DATA **t){
    if(t == NULL)
        return FALSE;
    if(*t == NULL)
        return FALSE;
    
    free((*t)->url);
    (*t)->url = NULL;

    free((*t)->title);
    (*t)->title = NULL;
    
    free(*t);
    *t = NULL;

    return TRUE;
}

char *tab_get_title(TAB_DATA *t){
    if(t == NULL) return NULL;

    return t->title;
}

boolean tab_set_title(TAB_DATA *t, char *title){
    if(t == NULL) return FALSE;

    t->title = title;
    return TRUE;
}

char *tab_get_url(TAB_DATA *t){
    if(t == NULL) return NULL;
    
    return  t->url;
}

boolean tab_set_url(TAB_DATA *t, char *url){
    if(t == NULL) return FALSE;

    t->url = url;
    return TRUE;
}

void tab_print(TAB_DATA *t){
    if(t == NULL) return;
    printf("%s %s\n", t->title, t->url);
}