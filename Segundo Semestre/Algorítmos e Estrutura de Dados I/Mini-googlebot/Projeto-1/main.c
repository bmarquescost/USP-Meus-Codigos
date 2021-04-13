/*
    ICMC - Instituto de Ciências Matemáticas e da Computação
    BCC  - Bacharelado em Ciências de Computação
    
    SCC0202 - ALGORITMOS E ESTRUTURAS DE DADOS I
    Docente: Rudinei Goularte 

    Aluno: Bernardo Marques Costa                    Número USP: 11795551
    Aluno: Fernando Henrique Paes Generich           Número USP: 11795342

    MINI GOOGLEBOT 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "website.h"
#include "util.h"
#include "menu.h"
#include "listaencadeada.h"

int main(int argc, char *argv[]){
    // imprimindo o cabeçalho do programa
    printf("______________________________________________________________\n");
    printf("\n                       GOOGLEBOT                            \n");
    printf("______________________________________________________________\n\n");
    
    // Leitura do arquivo padrão "googlebot.txt"
    printf("Obtendo dados do arquivo padrão inicial ...\n\n");    
    
    LISTA *lista_sites;
    lista_sites = lista_criar();
    preenche_lista_dados_csv(lista_sites, ARQUIVO_GOOGLEBOT);
    if(lista_vazia(lista_sites) == FALSE) printf("Leitura de dados de Googlebot.txt bem sucedida.\n");
    
    // Executando o programa de interação com o usuário
    executa_programa(lista_sites);

    // Liberando a memória heap utilizada pelo programa.
    lista_deletar(&lista_sites);

    return 0;
}