/*
    Aluno: Bernardo Marques Costa
    nUSP: 11795551
*/
#include <stdio.h>
#include <stdlib.h>

#include "item.h"
#include "arvbinbusca.h"

struct _no {
    ITEM *chave;
    NO *esquerda;
    NO *direita;
};

struct _arvbinbusca {
    NO *raiz;
};

// Criação de uma instancia de arvore binária de busca 
ABB *arvore_bin_busca_criar(void) {
    // aloca com todos os valores zerados internamente
    ABB *nova_arvore = calloc(1,sizeof(ABB));
    return nova_arvore;
}

// Função privada de criação de nós para facilitar a alocação de novos nós 
static NO *_criar_no(ITEM *item) {
    NO *novo_no = calloc(1,sizeof(NO));
    
    if(novo_no != NULL) 
        novo_no->chave = item;

    return novo_no;
}

// Função privada para apagar nós, facilitando a deslocação
static void _apagar_nos(NO **raiz) {
    if(*raiz != NULL) {
        _apagar_nos(&(*raiz)->esquerda);
        _apagar_nos(&(*raiz)->direita);
        
        item_deletar(&(*raiz)->chave);
        free(*raiz);
        *raiz = NULL;
    }
}

// Função recursiva para eliminar uma arvore binaria de busca completamente
void arvore_bin_busca_deletar(ABB **arvore) {
    if(*arvore == NULL) return;
    _apagar_nos(&(*arvore)->raiz);
    free(*arvore);
    *arvore = NULL;
}

// Função privada de inserção recursiva
static NO *_inserir_recursivamente(NO *raiz, ITEM *item) {
    if(raiz == NULL)
       raiz = _criar_no(item);
    else if(item_pegar_chave(item) > item_pegar_chave(raiz->chave))
        raiz->direita = _inserir_recursivamente(raiz->direita, item);
    else if(item_pegar_chave(item) < item_pegar_chave(raiz->chave))
        raiz->esquerda = _inserir_recursivamente(raiz->esquerda, item);

    return raiz;
}

// Função para inserir um novo nó com a chave passada por parâmetro
void arvore_bin_busca_inserir(ABB *arvore, ITEM *item) {
    arvore->raiz = _inserir_recursivamente(arvore->raiz, item);
}

// Função privada utilizada para o caso da remoção de um nó interno (com 2 filhos)
// Troca o valor máximo (mais a direita) da sub-árvore esquerda do nó que desejamos remover
static void _trocar_max_esquerda(NO *troca, NO *raiz, NO *anterior) {
    if(troca->direita != NULL) {
        _trocar_max_esquerda(troca->direita, raiz, troca);
        return;
    }
    if(raiz == anterior)
        anterior->esquerda = troca->esquerda;
    else
        anterior->direita = troca->esquerda;
    raiz->chave = troca->chave;
    free(troca);
    troca = NULL;
}

// Função recursiva para a remoção de um nó
static int _remover_recursiva(NO **raiz, int chave) {
    NO *auxiliar;
    if(*raiz != NULL) {
    
        if(chave == item_pegar_chave((*raiz)->chave)) {
            // Caso do valor desejado a ser removido ser uma folha ou ter um único filho
            if((*raiz)->esquerda == NULL || (*raiz)->direita == NULL) {
                auxiliar = *raiz;
                if((*raiz)->esquerda == NULL)
                    *raiz = (*raiz)->direita;
                else 
                    *raiz = (*raiz)->esquerda;
                free(auxiliar);
                auxiliar = NULL;
            }
            // Caso seja um nó interno, tendo dois filhos (devemos posicionar o maior filho da sub-árvore esquerda
            // ou então o menor filho da sub-árvore direita)
            else {
                _trocar_max_esquerda((*raiz)->esquerda, *raiz, *raiz);
                return 1;
            }
        }
        // Percorrendo procurando a chave desejada para ser removida
        else {
            if(chave < item_pegar_chave((*raiz)->chave))
                return _remover_recursiva(&(*raiz)->esquerda, chave);
            else 
                return _remover_recursiva(&(*raiz)->direita, chave);
        }
    }
    return 0;
}

// Função para remoção de um nó da árvore binaria de busca
int arvore_bin_busca_remover(ABB *arvore, int chave) {
    if(arvore != NULL) 
        return _remover_recursiva(&arvore->raiz, chave);
    return 0;
}

// Função privada recursiva que busca uma chave na árvore
static ITEM *_consulta_recursiva(NO *raiz, int buscado) {
    if(raiz == NULL)
        return NULL;
    else {
        if(buscado == item_pegar_chave(raiz->chave)) 
            return raiz->chave;
        else {
            if(buscado < item_pegar_chave(raiz->chave))
                return _consulta_recursiva(raiz->esquerda, buscado);
            else
                return _consulta_recursiva(raiz->esquerda, buscado);
        }
    }
}

// Função de busca na árvore
ITEM *arvore_bin_busca_consulta(ABB *arvore, int chave) {
    return _consulta_recursiva(arvore->raiz, chave);
}

// Função privada recursiva que calcula a profundidade de uma árvore
static int _profundidade_recursiva(NO *raiz) {
    if(raiz == NULL)
        return 0;
    
    int altura_esquerda = _profundidade_recursiva(raiz->esquerda) + 1;
    int altura_direita = _profundidade_recursiva(raiz->direita) + 1;

    return (altura_esquerda > altura_direita) ? altura_esquerda : altura_direita;
}

// Função publica de calculo da profunidade de árvore
int arvore_bin_busca_profundidade(ABB *arvore) {
    if(arvore != NULL)
        return _profundidade_recursiva(arvore->raiz);
    return -1;
}

// Função privada recursiva que verfica se uma sub-árvore está perfeitamente balanceada
static int _perf_balanceada_recursiva(NO *raiz, int *profundidade) {
    if(raiz == NULL)
        return 1;
    
    int altura_direita = 0; 
    int altura_esquerda = 0;
    
    if(raiz == NULL) {
        *profundidade = 0;
        return 1;
    }   
    
    // Verifica se a sub-árvore esquerda está balanceada
    int esquerda_balanceada = _perf_balanceada_recursiva(raiz->esquerda, &altura_esquerda);
    // Veririca se a sub-árvore direita está balanceada
    int direita_balanceada = _perf_balanceada_recursiva(raiz->direita, &altura_direita);

    // Indica qual a profunidade da sub-árvore analisada (considera maior profunidade entre a sub-árvore direita e esquerda + 1)
    *profundidade = ((altura_direita > altura_esquerda) ? altura_direita : altura_esquerda) + 1;

    // Caso a altura de uma seja diferente da altura da outra por mais de 1 (maior igual que 2), a árvore não sera balanceada
    if(altura_direita > altura_esquerda) {
        if(altura_direita - altura_esquerda >= 2)
            return 0;
    }
    else
        if(altura_esquerda - altura_direita >= 2) 
            return 0; 
    // Caso tenha passado pelas condições anteriores, verificamos as booleanas que representam se as sub-árvores à esquerda
    // e a direita são balanceadas (só será 1 se ambas forem balanceadas)
    return esquerda_balanceada && direita_balanceada;   
}

// Função pública para verificar se uma árvore está perfeitamente balanceada
int abb_perfeitamente_balanceada(ABB *arvore) {
    if(arvore == NULL)
        return 1;
    int altura = 0;
    return _perf_balanceada_recursiva(arvore->raiz, &altura);
}

// Função privada e recursiva para impressão da árvore e seus nós
static void _imprimir_arvore_recursiva(NO *raiz) {
	if(raiz != NULL) {
        item_imprimir(raiz->chave);
        printf("(");
		_imprimir_arvore_recursiva(raiz->esquerda);
		printf(",");
		_imprimir_arvore_recursiva(raiz->direita);
		printf(")");
	}
	else printf("null");
}

// Função pública para impressão da árvore
void arvore_bin_busca_imprimir(ABB *arvore) {
    _imprimir_arvore_recursiva(arvore->raiz);
    printf("\n");
}