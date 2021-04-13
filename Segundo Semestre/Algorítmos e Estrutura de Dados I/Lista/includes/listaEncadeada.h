#ifndef LISTA_H
#define LISTA_H

	#define TAM_MAX 100 /*estimativa do tamanho máximo da lista*/
	#define TRUE 1 
	#define FALSE 0
	#define boolean int /*define um tipo booleano*/
	#define inicial 0
	#define ERRO -32000

	#include "item.h"

	typedef struct _lista LISTA;

	LISTA *lista_criar(void);
	void lista_apagar(LISTA **lista);
	
    boolean lista_inserir(LISTA *lista, ITEM *item);
	boolean lista_remover(LISTA *lista, int chave);
	
    ITEM *lista_busca(LISTA *lista, int chave);

	int lista_tamanho(LISTA *lista);
	boolean lista_vazia(LISTA *lista);
	boolean lista_cheia(LISTA *lista);
	
    void lista_inverter(LISTA *lista);

    void lista_imprimir(LISTA *lista);
    
#endif