/*
    ICMC - Instituto de Ciências Matemáticas e da Computação
    BCC  - Bacharelado em Ciências de Computação
    
    SCC0202 - ALGORITMOS E ESTRUTURAS DE DADOS I
    Docente: Rudinei Goulart 

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
#include "avl.h"

int main(int argc, char *argv[]){
    // imprimindo o cabeçalho do programa
    printf("+--------------------------------------------------------------+\n");
    printf("|                      MINI - GOOGLEBOT                        |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("%60s\n\n", "o retorno parte 2...");
    
    // Leitura do arquivo padrão "googlebot.txt"
    printf("Obtendo dados do arquivo padrão inicial ...\n\n");    
    
    AVL *arvore_sites = NULL;
    arvore_sites = avl_criar();
    
    preenche_lista_dados_csv(arvore_sites, ARQUIVO_GOOGLEBOT);
    
    if(!avl_vazia(arvore_sites)) printf("Leitura de dados de Googlebot.txt bem sucedida.\n");
    
    //Executando o programa de interação com o usuário
    executa_programa(arvore_sites);

    // Liberando a memória heap utilizada pelo programa.
    avl_deletar(&arvore_sites);
    
    return 0;
}