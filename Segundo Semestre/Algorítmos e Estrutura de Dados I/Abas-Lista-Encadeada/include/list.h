#ifndef _LIST_H_
#define _LIST_H_

typedef struct _list LIST;
typedef struct _node NODE;
#include "tab.h"

LIST *list_create();
boolean list_delete(LIST **l);

boolean list_push(LIST *l, TAB_DATA *tab);

NODE *list_pop(LIST *l, char *title);

TAB_DATA *list_find(LIST *l, char *title);

int list_size(LIST *l);
boolean list_empy(LIST *l);
boolean list_full(LIST *l);

boolean list_check_existence(LIST *l, char *title);

boolean list_change_pos(LIST *l, char *title, int index);

void list_print(LIST *l);


#endif
