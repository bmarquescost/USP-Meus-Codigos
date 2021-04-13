/*
    Aluno: Bernardo Marques Costa
    nUSP: 11795551
*/
#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "arvbinbusca.h"


int main(int argc, char *argv[]) {
    ABB  *arvore_perf_balanceada = arvore_bin_busca_criar();
    
    // Árvore balanceada
    arvore_bin_busca_inserir(arvore_perf_balanceada, item_criar(10));
    arvore_bin_busca_inserir(arvore_perf_balanceada, item_criar(21));
    arvore_bin_busca_inserir(arvore_perf_balanceada, item_criar(5));
    arvore_bin_busca_inserir(arvore_perf_balanceada, item_criar(2));
    arvore_bin_busca_inserir(arvore_perf_balanceada, item_criar(9));
    arvore_bin_busca_inserir(arvore_perf_balanceada, item_criar(18));
    arvore_bin_busca_inserir(arvore_perf_balanceada, item_criar(42));
    arvore_bin_busca_inserir(arvore_perf_balanceada, item_criar(100));
    arvore_bin_busca_inserir(arvore_perf_balanceada, item_criar(30));
    
    arvore_bin_busca_imprimir(arvore_perf_balanceada);
    if(abb_perfeitamente_balanceada(arvore_perf_balanceada))
        printf("A arvore está perfeitamente balanceada\n");
    else 
        printf("A árvore não está balanceada\n");
    
    arvore_bin_busca_deletar(&arvore_perf_balanceada);

    // Árvore não balanceada
    ABB  *arvore_nao_balanceada = arvore_bin_busca_criar();
    arvore_bin_busca_inserir(arvore_nao_balanceada, item_criar(50));
    arvore_bin_busca_inserir(arvore_nao_balanceada, item_criar(43));
    arvore_bin_busca_inserir(arvore_nao_balanceada, item_criar(20));
    arvore_bin_busca_inserir(arvore_nao_balanceada, item_criar(10));
    arvore_bin_busca_inserir(arvore_nao_balanceada, item_criar(72));
    arvore_bin_busca_inserir(arvore_nao_balanceada, item_criar(80));
    
    arvore_bin_busca_imprimir(arvore_nao_balanceada);
    if(abb_perfeitamente_balanceada(arvore_nao_balanceada))
        printf("A arvore está perfeitamente balanceada\n");
    else 
        printf("A árvore não está balanceada\n");
    
    arvore_bin_busca_deletar(&arvore_nao_balanceada);

    return 0;
}