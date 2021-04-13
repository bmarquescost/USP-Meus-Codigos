/*
    Aluno: Bernardo Marques Costa
    nUSP: 11795551
*/
#ifndef _ABB_H_
#define _ABB_H_

typedef struct _arvbinbusca ABB;
typedef struct _no NO;

ABB *arvore_bin_busca_criar(void);
void arvore_bin_busca_inserir(ABB *arvore, ITEM *item);
int arvore_bin_busca_remover(ABB *arvore, int chave);
ITEM *arvore_bin_busca_consulta(ABB *arvore, int chave);
void arvore_bin_busca_imprimir(ABB *arvore);
void arvore_bin_busca_deletar(ABB **arvore);
int abb_perfeitamente_balanceada(ABB *arvore);


#endif