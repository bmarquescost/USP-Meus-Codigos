#ifndef _TAB_H_
#define _TAB_H_

#define boolean int
#define TRUE 1
#define FALSE 0
#define ERROR -32000

typedef struct _tab TAB_DATA;

TAB_DATA *tab_create();

boolean tab_delete(TAB_DATA **t);

char *tab_get_title(TAB_DATA *t);
boolean tab_set_title(TAB_DATA *t, char *title);

char *tab_get_url(TAB_DATA *t);
boolean tab_set_url(TAB_DATA *t, char *url);

void tab_print(TAB_DATA *t);

#endif