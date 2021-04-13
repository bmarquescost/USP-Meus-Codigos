#ifndef _ITEM_H_
#define _ITEM_H_

    typedef struct _item ITEM;

    #define TAM_MAX 100 /*estimativa do tamanho máximo da lista*/
	#define TRUE 1 
	#define FALSE 0
	#define boolean int /*define um tipo booleano*/
	#define inicial 0
	#define ERRO -32000
    
    ITEM *item_criar(int chave);
    boolean item_apagar(ITEM **item);
    int item_get_chave(ITEM *item);
    boolean item_set_chave(ITEM *item, int n);

#endif