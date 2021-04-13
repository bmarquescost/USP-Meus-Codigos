#include "racional.h"
#include<stdio.h>

int main() {
   /*RACIONAL racional1;*/

   RACIONAL *rac1 = criar(5,3);
   RACIONAL *rac2 = criar(2,4);

   RACIONAL *rac3 = adicao(rac1, rac2);

   imprimir(rac3);

   /*printf("%d \n",rac1->num);*/ /*Erro: não pode acessar valores do TAD diretamente*/

   apagar(rac1);
   apagar(rac2);
   apagar(rac3);
   
   return 0;
}
