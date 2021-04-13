/*
    SCC0202 - ALGORITMOS E ESTRUTURAS DE DADOS I
    Docente: Rudinei Goularte 

    Aluno: Bernardo Marques Costa                    Número USP: 11795551
    Aluno: Fernando Henrique Paes Generich           Número USP: 11795342

    MINI GOOGLEBOT 
*/
#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>
#include <stdlib.h>

#include "listaencadeada.h"

#define TAM 128
#define TOKEN ','
#define ARQUIVO_GOOGLEBOT "googlebot.txt"

char *leitura_de_linha(FILE *stream);
char **leitura_csv(char *nome_csv, int *num_linhas);
char *particiona_string_pelo_token(char *linha_inteira, int inicio, boolean *acabou);
WEBSITE *cria_website_pelos_dados(char *linha_inteira);
void preenche_lista_dados_csv(LISTA *l, char *arquivo_csv);

#endif