#ifndef _ARVORE_BINARIA_H_
#define _ARVORE_BINARIA_H_

#define INSERIR_ESQUERDA -1
#define INSERIR_DIREITA 1

typedef struct _arvore_bin ARVORE_BIN;

ARVORE_BIN *criar_arvore(void);
int arvore_inserir(ARVORE_BIN *arvore, int item, int lado, int chave_pai);
int altura_da_arvore(ARVORE_BIN *arvore);
void arvore_imprimir(ARVORE_BIN *arvore);
int nos_da_arvore(ARVORE_BIN *arvore);
void apagar_arvore_binaria(ARVORE_BIN **arvore);

#endif