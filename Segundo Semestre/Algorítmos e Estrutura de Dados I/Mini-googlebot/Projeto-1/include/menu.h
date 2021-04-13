/*
    SCC0202 - ALGORITMOS E ESTRUTURAS DE DADOS I
    Docente: Rudinei Goularte 

    Aluno: Bernardo Marques Costa                    Número USP: 11795551
    Aluno: Fernando Henrique Paes Generich           Número USP: 11795342

    MINI GOOGLEBOT 
*/
#ifndef _MENU_H_
#define _MENU_H_

#include "listaencadeada.h"

void imprime_menu_complexo();
void executa_programa();
void imprime_menu();
boolean cria_site_insere_na_lista(LISTA *l, int codigo, char *nome,  char *url, int relevancia, char **pc, int n_pc);
void carrega_dados_csv(LISTA *lista);

#endif