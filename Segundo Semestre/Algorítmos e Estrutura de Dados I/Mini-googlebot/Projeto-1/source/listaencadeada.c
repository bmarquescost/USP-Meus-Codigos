/*
    SCC0202 - ALGORITMOS E ESTRUTURAS DE DADOS I
    Docente: Rudinei Goularte 

    Aluno: Bernardo Marques Costa                    Número USP: 11795551
    Aluno: Fernando Henrique Paes Generich           Número USP: 11795342

    MINI GOOGLEBOT 
*/

#include <stdio.h>
#include <stdlib.h>

#include "listaencadeada.h"
#include "website.h"

typedef struct _no NO;

/*
    Estrutura dos nós a serem inseridos na Lista Encadeada
*/
struct _no {
    WEBSITE *site; 
    NO *proximo;
};

/*
    Estrutura da Lista Encadeada
*/
struct _lista {
    NO* inicio;    
    int num_nos;
};

/*
    Função criar_no
    Recebe como parâmetro um website e cria um nó para ele
    Retorna o nó criado
*/
NO *criar_no(WEBSITE *site) {
    
    NO *no_novo = calloc(1,sizeof(NO));
    no_novo->site = site;
    no_novo->proximo = NULL;
    
    return no_novo;
}

/*
    Função deletar_no
    Recebe como parâmetro o no a ser deletado e efetua a remoção
    Retorna um booleano conforme for verificada a possibilidade ou não de remoção
*/
boolean deletar_no(NO *no_deletado){
    if(no_deletado == NULL)
        return FALSE;
    
    website_deletar(&no_deletado->site);
    
    no_deletado->site = NULL;
    
    free(no_deletado);
    no_deletado = NULL;
    
    return TRUE;
}

/*
    Função lista_criar
    Não recebe parâmetros, cria uma lista e seta seus dados para 0
*/
LISTA *lista_criar(void) {
    LISTA *nova_lista = calloc(1, sizeof(LISTA));
   
    nova_lista->inicio = NULL;
    nova_lista->num_nos = 0;
    
    return nova_lista;
}

/*
    Função lista_deletar
    Recebe como parâmetro o endereço da lista a ser deletada
    Retorna um booleano conforme for verificada a possibilidade ou não de deleção da lista
*/
boolean lista_deletar(LISTA **lista) {
    if(lista == NULL){
        printf("Erro ao apagar lista (lista inexistente).\n");
        return FALSE;
    }
    if(*lista == NULL)
            free((*lista));
    
    else {
        NO *no_apagado = (*lista)->inicio;
        
        while(no_apagado != NULL) {
            (*lista)->inicio = no_apagado->proximo;
            deletar_no(no_apagado);
            
            no_apagado = (*lista)->inicio;
        }
        free(*lista);
    }
    return TRUE;
}

/*
    Função lista_inserir
    Recebe como parâmetros a lista e o website que srá inserido nela
    Retorna um booleano conforme for verificada a possibilidade ou não de inserção
*/
boolean lista_inserir(LISTA *lista, WEBSITE *site) {
    if(lista == NULL || site == NULL) {
        printf("Erro ao inserir site na lista (site ou lista inexistente).\n");
        return FALSE;
    }

    NO *no_novo = criar_no(site); 
    
    if(lista->num_nos == 0) {
        lista->inicio = no_novo;
        no_novo->proximo = NULL;
    }

    else {
        NO *anterior = NULL;
        NO *atual = lista->inicio;
        
        int codigo_site = website_consulta_codigo(site);
        int codigo_atual = website_consulta_codigo(atual->site);
        
        while(atual != NULL){
            codigo_atual = website_consulta_codigo(atual->site);   
            if(codigo_site < codigo_atual) break;
            anterior = atual;
            atual = atual->proximo;
        }

        if(atual == lista->inicio) {
            no_novo->proximo = lista->inicio;
            lista->inicio = no_novo;
        }

        else {
            no_novo->proximo = anterior->proximo;
            anterior->proximo = no_novo;
        }
    }
    ++lista->num_nos;

    return TRUE;
}

/*
    Função lista_remover
    Recebe como parâmetros a lista e o código do website que será removido dela
    Retorna um booleano conforme for verificada a possibilidade ou não de remoção
*/
boolean lista_remover(LISTA *lista, int codigo) {
    if(lista == NULL) {
        printf("Erro ao remover nó de uma lista (lista inexistente).\n");
        return FALSE;
    }
    
    NO *no_atual = lista->inicio;
    NO *no_anterior = NULL;
    
    int codigo_no;

    while(no_atual != NULL) {
        codigo_no = website_consulta_codigo(no_atual->site);        
        
        if(codigo_no == codigo) {
            if(no_anterior != NULL) no_anterior->proximo = no_atual->proximo;
            else lista->inicio = no_atual->proximo;
            
            website_deletar(&no_atual->site);
            free(no_atual);   
            --lista->num_nos;
            return TRUE; 
        }

        no_anterior = no_atual;
        no_atual = no_atual->proximo;
    }
    return FALSE;
}   

/*
    Função lista_busca
    Recebe como parâmetros a lista e o código do website que será buscado nela
    Retorna o website buscado em caso de sucesso ou NULL para uma lista vazia
*/
WEBSITE *lista_busca(LISTA *lista, int codigo) {
    if(lista == NULL) {
        printf("Erro ao buscar codigo em lista (lista vazia).\n");
        return NULL;
    }
    
    NO *auxiliar = lista->inicio;
    int codigo_no;
    while(auxiliar != NULL){
        codigo_no = website_consulta_codigo(auxiliar->site);
        if(codigo_no == codigo) break;
        auxiliar = auxiliar->proximo;
    }

    return auxiliar->site;
}   

/*
    Função lista_procurar_codigo
    Recebe como parâmetros a lista e o código procurado(auxilia a inserção de websites sem a repetição de códigos)
    Retorna um booleano conforme for verificada a existência ou não do código na lista
*/
boolean lista_procurar_codigo(LISTA *lista, int codigo){
    if(lista == NULL){
        printf("Lista inexistente, impossivel buscar a codigo\n");
        return FALSE;
    }
    
    NO *no_aux = lista->inicio;

    while (no_aux != NULL){
        if(codigo == website_consulta_codigo(no_aux->site))
            return TRUE;
        no_aux = no_aux->proximo;
    }

    return FALSE;    
}

/*
    Função lista_tamanho
    Recebe como parâmetro a lista cujo tamanho será verificado
    Retorna um inteiro com o número de nós da lista em caso de sucesso ou ERRO para uma lista inexistente
*/
int lista_tamanho(LISTA *lista){
    if(lista == NULL) {
        printf("Erro ao ler tamanho da lista (lista inexistente).\n");
        return ERRO;
    }

    return lista->num_nos;
}

/*
    Função lista_vazia
    Recebe como parâmetro a lista que será verificada
    Retorna um booleano conforme for verificado se a lista está ou não vazia
*/
boolean lista_vazia(LISTA *lista){
    if(lista == NULL) {
        printf("Erro ao verificar se a lista está vazia (lista inexistente).\n");
        return FALSE;
    }
    return  lista->num_nos == 0;
}

/*
    Função lista_cheia
    Recebe como parâmetro a lista que será verificada
    Retorna um booleano conforme for verificado se a lista está ou não cheia
*/
boolean lista_cheia(LISTA *lista){
    return FALSE; // Nunca é uma lista cheia, já que é alocada dinamicamente
}

/*
    Função lista_mostrar
    Recebe como parâmetro a lista a ser mostrada e imprime os sites nela presentes com mostrar_site
*/
void lista_mostrar(LISTA *l){
    if(l == NULL){
        return;
    }
    
    if(l->num_nos == 0){
        printf("Lista está vazia neste momento, insira mais dados.\n");
        return;
    }

    NO *aux = l->inicio;
    while(aux != NULL){
        mostrar_site(aux->site);    
        aux = aux->proximo;
    }
}
