#include <stdio.h>
#include <stdlib.h>

#include "palavras_chave.h"

#define QUANTIDADE_PADRAO 10


// Struct padrão que armazena uma lista de sites: sendo utilizada para ambas as funções extras
struct _lista_sites {
    WEBSITE **sites;   // Lista de sites
    int qtd_sites;     // Quantidade de sites na lista
    int multiplicador; // Auxiliar para realocaçäo da lista de sites (para que não seja necessário realocar memória a toda nova inserção de sites na lista)
};

// Struct utilizada para a sugestões de site 
struct _sugestoes {
    LISTA_SITES *lista_sites; // Armazena uma lista de sites que possuem ao menos uma daquelas palavras chave
    TRIE *palavras_chave;     // Estrutura de dados que armazena todas as palavras chaves existentes
    int qtd_palavras_chave;   // Variável que armazena a quantidade de palavras chaves total
};

// Struct que armazena todos os sites que possuem dada palavra entre suas palavras chave
struct _mesmas_palavra_chave {
    LISTA_SITES *lista_sites; // Lista de sites
    char *palavra_chave;      // Palavra chave que está relacionada a todas estes sites na lista
};

/*
    Função lista_sites_criar:
    Inicia uma nova instancia de lista de sites
*/
LISTA_SITES *lista_sites_criar(void) {
    LISTA_SITES *nova_lista = calloc(1, sizeof(LISTA_SITES));
    
    nova_lista->sites = NULL;
    nova_lista->qtd_sites = 0;
    nova_lista->multiplicador = 1;

    return nova_lista;
}

void lista_sites_deletar(LISTA_SITES **lista_apagada) {
    if(*lista_apagada == NULL) return;

    free((*lista_apagada)->sites);
    (*lista_apagada)->sites = NULL;

    free(*lista_apagada);
    *lista_apagada = NULL;
}

void lista_sites_inserir_site(LISTA_SITES *l, WEBSITE *site) {
    if(l == NULL || site == NULL) return;

    if(l->qtd_sites % QUANTIDADE_PADRAO == 0) {
        long int tamanho = QUANTIDADE_PADRAO * (++(l->multiplicador) * sizeof(WEBSITE *));
        l->sites = realloc(l->sites, tamanho);
    }

    l->sites[l->qtd_sites] = site;
    ++l->qtd_sites;
}


int lista_sites_consulta_num_sites(LISTA_SITES *l) {
    if(l == NULL) return ERRO;

    return l->qtd_sites;
}



/* 
    Função palavras_chave_criar:
    Inicia uma nova instancia da struct MSM_PALAVRA, usada para a primeira função
*/
MSM_PALAVRA *msm_palavra_chave_criar() {
    MSM_PALAVRA *nova_lista = calloc(1, sizeof(MSM_PALAVRA));
    
    nova_lista->palavra_chave = NULL;
    nova_lista->lista_sites = calloc(1, sizeof(LISTA_SITES));
    nova_lista->lista_sites->multiplicador = 1;
    
    return nova_lista;
}

/* 
    Função palavras_chave_deletar:
*/
void msm_palavra_chave_deletar(MSM_PALAVRA **sites_encontrados) {
    if(*sites_encontrados == NULL) return;   

    lista_sites_deletar(&(*sites_encontrados)->lista_sites);

    free((*sites_encontrados));
    (*sites_encontrados) = NULL;
}

void msm_palavra_chave_alterar_palavra(MSM_PALAVRA *lista, char *palavra_chave) {
    if(lista == NULL || palavra_chave == NULL) return;

    lista->palavra_chave = palavra_chave;
}

void msm_palavra_chave_inserir_site(MSM_PALAVRA *sites_msm_palavra, WEBSITE *site_encontrado) {
    if(sites_msm_palavra == NULL || site_encontrado == NULL) return;

    
}

void printar_lista_encontrada(LISTA_SITES *sites_encontrados){
    if(sites_encontrados == NULL) return;

    if(sites_encontrados->qtd_sites == 0 || sites_encontrados->sites == NULL) 
        return;
    
    printf("\n+---------------------------------------------------------------+\n");
    for(int i = 0; i < sites_encontrados->qtd_sites ; ++i) {
        printf("| [%d] %s\n", i, website_consulta_nome(sites_encontrados->sites[i]));
        printf("|\tRelevância: %d \n|\tURL: %s\n",  website_consulta_relevancia(sites_encontrados->sites[i]), website_consulta_url(sites_encontrados->sites[i]));
        if(i + 1 != sites_encontrados->qtd_sites) printf("|\n");
    }
    
    printf("+---------------------------------------------------------------+\n");

}

TRIE *construir_trie_com_lista_sites(LISTA_SITES *l) {
    if(l == NULL) return NULL;

    TRIE *palavras_chave = trie_criar();
    
    for(int i = 0; i < l->qtd_sites; ++i) {
        char **palavras_do_site = website_consulta_palavras_chave(l->sites[i]);
        
        for(int j = 0; j < website_consulta_num_palavras_chave(l->sites[i]); ++j)
            trie_inserir_palavra(palavras_chave, palavras_do_site[j]);
    }

    return palavras_chave;
}


static void min_heapify(WEBSITE **s, int indice, int n) {
    
    int menor = indice;
    int filho_esquerda = indice * 2 + 1; 
    int filho_direita = indice * 2 + 2;
    
    
    if(filho_esquerda < n && website_consulta_relevancia(s[filho_esquerda]) < website_consulta_relevancia(s[menor])) 
        menor = filho_esquerda;
    
    if(filho_direita < n && website_consulta_relevancia(s[filho_direita]) < website_consulta_relevancia(s[menor])) 
        menor = filho_direita;
        
    if(menor != indice) {
        WEBSITE *tmp = s[indice];
        s[indice] = s[menor];
        s[menor] = tmp;

        min_heapify(s, menor, n);
    }

}

static void heapsort(WEBSITE **s, int n) {
    for(int i = n/2 - 1; i >= 0; --i)
        min_heapify(s, i, n);

    for(int i = n - 1; i >= 0; --i){
        WEBSITE *tmp = s[0];
        s[0] = s[i];
        s[i] = tmp;

        min_heapify(s, 0, i);
    }
}

void lista_sites_ordenar(LISTA_SITES *lista_sites) {
    if(lista_sites == NULL) return;

    heapsort(lista_sites->sites, lista_sites->qtd_sites);
}

void msm_palavra_chave_ordenar(MSM_PALAVRA *sites_encontrados) {
    if(sites_encontrados == NULL) return;

    heapsort(sites_encontrados->lista_sites->sites, sites_encontrados->lista_sites->qtd_sites);
    
}
