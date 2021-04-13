/*********************************************
	Aluno: Bernardo Marques Costa
	Número USP: 11795551

	Cálculo do número de nós de uma árvore
**********************************************/

#include <stdio.h>
#include <stdlib.h>

#include "arvorebinaria.h"

int main(int argc, char *argv[]) {

    ARVORE_BIN *arvore = criar_arvore();

    arvore_inserir(arvore, 10, -1, 0);    // Inserindo um nó contendo dado inteiro 10 (inserido na raiz)
    arvore_inserir(arvore, 21, 1, 10);    // Inserindo um nó ao lado direito da raiz da árvore, valor 21 com nó pai 10
    arvore_inserir(arvore, 321, -1, 10);  // Inserindo um nó ao lado esquerdo da raiz da árvore, valor 321 com nó pai 10
    arvore_inserir(arvore, 189, 1, 21);   // Inserindo um nó ao lado direito do nó de valor 21, valor de 189 
    arvore_inserir(arvore, 2, -1, 21);    // Inserindo um nó ao lado esquerdo do nó de valor 21, de valor 2
   
    /*
        Árvore criada: 
      |              10
      |            /    \
      |          21    321
      |         /  \
      |       189    2    
      `-> Altura 3
    */

    printf("Qtd de nós na árvore: %d\n", nos_da_arvore(arvore));

    apagar_arvore_binaria(&arvore);

    return 0;
}