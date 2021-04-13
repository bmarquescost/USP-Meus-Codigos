#include <stdio.h>
#include <stdlib.h>

#include "util.h"
#include "avl.h"
#include "trie.h"
#include "palavras_chave.h"

#define boolean int
#define TRUE 1
#define FALSE 0

typedef struct _no NO;

#define _max(a,b) (a >= b ? a : b)

struct _no {
    WEBSITE *site;
    NO *esquerda;
    NO *direita;
    int altura;
};

struct _avl {
    NO *raiz;
    int num_sites;
};


AVL *avl_criar(void) {
    // Devido ao calloc teremos tudo com NULL ou 0
    AVL *nova_arvore = calloc(1, sizeof(AVL));
    return nova_arvore;
}

static NO *_avl_criar_no(WEBSITE *site) {
    // Cria um novo nó     
    NO *novo_no = calloc(1,sizeof(NO));
    novo_no->site = site;
    novo_no->altura = -1; // por ser um nó qualquer, não inserido, sua altura será indicada por -1

    return novo_no;
}


static void _avl_deletar_no(NO **raiz) {
    if(*raiz != NULL) {
        _avl_deletar_no(&(*raiz)->esquerda);
        _avl_deletar_no(&(*raiz)->direita);
        website_deletar(&(*raiz)->site);
        free(*raiz);
        *raiz = NULL;
    }
}

void avl_deletar(AVL **arvore) {
    if(*arvore != NULL) {
        _avl_deletar_no(&(*arvore)->raiz);
        free(*arvore);
        *arvore = NULL;
    }
}

static int _avl_altura_no(NO *no) {
    if(no == NULL)
        return -1;
    int altura_esquerda = _avl_altura_no(no->esquerda) + 1;
    int altura_direita = _avl_altura_no(no->direita) + 1;

    return _max(altura_esquerda, altura_direita);
}

int avl_altura(NO *no) {
    if(no == NULL) return -1;
    return no->altura;
}

static int _avl_fator_balanceamento(NO *no) {
    if(no == NULL) return 0;

    int altura_esquerda = avl_altura(no->esquerda);
    int altura_direita = avl_altura(no->direita);

    return altura_esquerda - altura_direita;
}

static NO *_avl_rotacionar_para_direita(NO *desbalanceado) {
    // Rotação
    NO *nova_raiz = desbalanceado->esquerda;
    desbalanceado->esquerda = nova_raiz->direita;
    nova_raiz->direita = desbalanceado;

    // Atualizando alturas
    desbalanceado->altura = _max(_avl_altura_no(desbalanceado->esquerda), _avl_altura_no(desbalanceado->direita)) + 1;
    nova_raiz->altura = _max(_avl_altura_no(nova_raiz->esquerda), _avl_altura_no(nova_raiz->direita)) + 1;

    return nova_raiz;
}


static NO *_avl_rotacionar_para_esquerda(NO *desbalanceado) {
    // Rotação
    NO *nova_raiz = desbalanceado->direita;
    desbalanceado->direita = nova_raiz->esquerda;
    nova_raiz->esquerda = desbalanceado;

    // Atualizando alturas
    desbalanceado->altura = _max(_avl_altura_no(desbalanceado->esquerda), _avl_altura_no(desbalanceado->direita)) + 1;
    nova_raiz->altura = _max(_avl_altura_no(nova_raiz->esquerda), _avl_altura_no(nova_raiz->direita)) + 1;

    return nova_raiz;
}

static NO *_avl_rotacionar_direita_esquerda(NO *desbalanceado) {
    desbalanceado->direita = _avl_rotacionar_para_direita(desbalanceado->direita);
    return _avl_rotacionar_para_esquerda(desbalanceado);
}

static NO *_avl_rotacionar_esquerda_direita(NO *desbalanceado) {
    desbalanceado->esquerda = _avl_rotacionar_para_esquerda(desbalanceado->esquerda);
    return _avl_rotacionar_para_direita(desbalanceado);
}

static NO *_avl_inserir_recursiva(NO *raiz, WEBSITE *novo_site, int *inseriu) {
    if(raiz == NULL) {
        raiz = _avl_criar_no(novo_site);
        *inseriu = TRUE;
    }
    
    // Procurando a inserção para a direita
    if(website_consulta_codigo(novo_site) > website_consulta_codigo(raiz->site)) {
        raiz->direita = _avl_inserir_recursiva(raiz->direita, novo_site, inseriu);
        
        if(_avl_fator_balanceamento(raiz) < -1) {
            if(website_consulta_codigo(novo_site) > website_consulta_codigo(raiz->direita->site))
                raiz = _avl_rotacionar_para_esquerda(raiz);
            else
                raiz = _avl_rotacionar_direita_esquerda(raiz);
        }
    }
    // Procurando a inserção para a esquerda
    else if(website_consulta_codigo(novo_site) < website_consulta_codigo(raiz->site)) {
        raiz->esquerda = _avl_inserir_recursiva(raiz->esquerda, novo_site, inseriu);

        if(_avl_fator_balanceamento(raiz) > 1) {
            if(website_consulta_codigo(novo_site) < website_consulta_codigo(raiz->esquerda->site))
                raiz = _avl_rotacionar_para_direita(raiz);
            else    
                raiz = _avl_rotacionar_esquerda_direita(raiz);
        }
    }

    raiz->altura = _max(_avl_altura_no(raiz->esquerda), _avl_altura_no(raiz->direita)) + 1;

    return raiz;
}

boolean avl_inserir_site(AVL *arvore, WEBSITE *site) {
    if(arvore == NULL || site == NULL) 
        return ERRO;

    boolean inseriu = FALSE;
    arvore->raiz = _avl_inserir_recursiva(arvore->raiz, site, &inseriu); 
    if(inseriu) arvore->num_sites++;
    
    return inseriu;
}

static NO *_pegar_menor_subarvore_direita(NO *raiz) {
    if(raiz == NULL) return NULL;
    NO *atual = raiz;

    while(atual->esquerda != NULL)
        atual = atual->esquerda;
    
    return atual;
}

static void _troca_max_esquerda(NO *troca, NO *raiz, NO *anterior) {
	if(troca->direita != NULL){
		_troca_max_esquerda(troca->direita, raiz, troca);
		return;
	}

	if(raiz == anterior)
		anterior->esquerda = troca->esquerda;
	else
		anterior->direita = troca->esquerda;
	
    website_deletar(&raiz->site);
	raiz->site = troca->site;

	free(troca);
	troca = NULL;
}

static NO *_avl_remover_no_recursiva(NO **raiz, int codigo_removido, int *removeu) {
    if(*raiz == NULL) {
        printf("Não foi encontrado o site requisitado para remoção\n");
        return NULL;
    }
    
    // Remoção deve está na sub-árvore a direita
    if(codigo_removido > website_consulta_codigo((*raiz)->site)) {
        (*raiz)->direita = _avl_remover_no_recursiva(&(*raiz)->direita, codigo_removido, removeu);
        (*raiz)->altura = _max(avl_altura((*raiz)->esquerda), avl_altura((*raiz)->direita)) + 1;
    }

    // Remoção deve estar na subárvore a esquerda
    else if(codigo_removido < website_consulta_codigo((*raiz)->site)) {
        (*raiz)->esquerda = _avl_remover_no_recursiva(&(*raiz)->esquerda, codigo_removido, removeu);
        (*raiz)->altura = _max(avl_altura((*raiz)->esquerda), avl_altura((*raiz)->direita)) + 1;
    }

    // Encontramos o que deve ser removido
    else {
        if((*raiz)->esquerda == NULL || (*raiz)->direita == NULL) {      
            NO *auxiliar_troca = *raiz;
            
            if((*raiz)->esquerda == NULL) 
                *raiz = (*raiz)->direita;

            else
                *raiz = (*raiz)->esquerda;
            
            website_deletar(&auxiliar_troca->site);
            free(auxiliar_troca);
            auxiliar_troca = NULL;

        }
        else 
            _troca_max_esquerda((*raiz)->esquerda, *raiz, *raiz);
        
        *removeu = TRUE;
    }

    if((*raiz) != NULL) {

        int fator_balanceamento = _avl_fator_balanceamento((*raiz));

        if(fator_balanceamento > 1) {
            fator_balanceamento = _avl_fator_balanceamento((*raiz)->esquerda);
            if(fator_balanceamento > 0)
                *raiz = _avl_rotacionar_para_direita(*raiz);
            else 
                *raiz = _avl_rotacionar_esquerda_direita(*raiz);
        }

        if(fator_balanceamento < -1) {
            fator_balanceamento = _avl_fator_balanceamento((*raiz)->direita);
            if(fator_balanceamento > 0)
                *raiz = _avl_rotacionar_para_esquerda(*raiz);
            else
                *raiz = _avl_rotacionar_direita_esquerda(*raiz);
        }
    }
    
    return *raiz;
}

boolean avl_remover_site(AVL *arvore, int codigo) {
    if(arvore == NULL) 
        return FALSE;
    int removeu = FALSE;

    arvore->raiz = _avl_remover_no_recursiva(&arvore->raiz, codigo, &removeu);

    if(removeu) arvore->num_sites--;

    return removeu;
}

static boolean _avl_procurar_codigo_recursiva(NO *raiz, int codigo) {
    if(raiz == NULL)
        return FALSE;

    if(codigo == website_consulta_codigo(raiz->site))
        return TRUE;

    if(codigo > website_consulta_codigo(raiz->site))
        return _avl_procurar_codigo_recursiva(raiz->direita, codigo);
    
    else if(codigo < website_consulta_codigo(raiz->site))
        return _avl_procurar_codigo_recursiva(raiz->esquerda, codigo);
    
    return FALSE;
}

boolean avl_procurar_codigo(AVL *arvore, int codigo) {
    if(arvore == NULL) {
        printf("Procura de código em árvore inexistente");
        return FALSE;
    }
    return _avl_procurar_codigo_recursiva(arvore->raiz, codigo);
}

boolean avl_vazia(AVL *arvore) {
    if(arvore == NULL) 
        return -1;
    
    return arvore->num_sites == 0;
}

static NO *_avl_procurar_codigo(NO *raiz, int codigo) {
    if(raiz == NULL) 
        return NULL;
    
    if(codigo > website_consulta_codigo(raiz->site))
        return _avl_procurar_codigo(raiz->direita, codigo);
    else if(codigo < website_consulta_codigo(raiz->site))
        return _avl_procurar_codigo(raiz->esquerda, codigo);
    
    else
        return raiz;
    
    return NULL;
}

WEBSITE *avl_buscar_site(AVL *arvore, int codigo) {
    if(arvore == NULL) {
        printf("Busca em árvore inexistente\n");
        return NULL;
    }

    NO *no_site_buscado = _avl_procurar_codigo(arvore->raiz, codigo);

    if(no_site_buscado != NULL) return no_site_buscado->site;

    printf("Site buscado inexistente\n");
    return NULL;
}

int avl_num_sites(AVL *arvore) {
    if(arvore == NULL) return ERRO;
    return arvore->num_sites;
}

// FUNÇÕES PARA IMPRIMIR INFORMAÇÕES DA ÁRVORE
static void _avl_imprimir_recursiva(NO *raiz) {
    if(raiz != NULL) {
        _avl_imprimir_recursiva(raiz->esquerda);
        mostrar_site(raiz->site);
        _avl_imprimir_recursiva(raiz->direita);
    }
}

static void _avl_imprimir_recursiva_pre_order(NO *raiz) {
    if(raiz != NULL) {
        mostrar_site(raiz->site);
        _avl_imprimir_recursiva_pre_order(raiz->esquerda);
        _avl_imprimir_recursiva_pre_order(raiz->direita);
    }
}

void avl_imprimir_em_ordem(AVL *arvore) {
    if(arvore == NULL)
        printf("Nada a ser mostrado: árvore vazia\n");
    else 
        _avl_imprimir_recursiva(arvore->raiz);
}

void avl_imprimir_pre_ordem(AVL *arvore) {
    if(arvore == NULL)
        printf("Nada a ser mostrado: árvore vazia\n");
    else
        _avl_imprimir_recursiva_pre_order(arvore->raiz);
}

/*
*/
static void _avl_buscar_palavra_recursiva(NO *no, char *palavra_chave, LISTA_SITES *sites_encontrados) {
    if(no == NULL) return;

    _avl_buscar_palavra_recursiva(no->esquerda, palavra_chave, sites_encontrados);
    
    if(verifica_palavra_chave(no->site, palavra_chave))
        lista_sites_inserir_site(sites_encontrados, no->site);

    _avl_buscar_palavra_recursiva(no->direita, palavra_chave, sites_encontrados);
}


LISTA_SITES *avl_buscar_palavra_chave(AVL *arvore, char *palavra_chave) {
    if(palavra_chave == NULL || arvore == NULL) return NULL;

    LISTA_SITES *sites_encontrados = lista_sites_criar();

    _avl_buscar_palavra_recursiva(arvore->raiz, palavra_chave, sites_encontrados);

    return sites_encontrados;
}

static void _avl_verificar_na_trie(NO *no, LISTA_SITES *sugestoes, TRIE *palavras) {
    if(no == NULL) return;

    _avl_verificar_na_trie(no->esquerda, sugestoes, palavras);
    
    char **palavras_chave_site = website_consulta_palavras_chave(no->site);
    for(int i = 0; i < website_consulta_num_palavras_chave(no->site); ++i) {
        if(trie_procurar_palavra(palavras, palavras_chave_site[i])) {
            lista_sites_inserir_site(sugestoes, no->site);
            break;
        }
    }

    _avl_verificar_na_trie(no->direita, sugestoes, palavras);
}

LISTA_SITES *verificar_sites_para_sugestao(AVL *arvore, TRIE *palavras_chave) {
    if(arvore == NULL || palavras_chave == NULL) return NULL;

    LISTA_SITES *sites_sugeridos = lista_sites_criar();

    _avl_verificar_na_trie(arvore->raiz, sites_sugeridos, palavras_chave);

    lista_sites_ordenar(sites_sugeridos);

    return sites_sugeridos;
}
