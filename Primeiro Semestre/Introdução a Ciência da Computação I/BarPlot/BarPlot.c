/*
    BAR PLOT
    ALUNO: Bernardo Marques Costa
    NÚMERO USP: 11795551

    Programa que receberá o número de valores que serão avaliados, e construirá uma ferramenta visual de acordo a frequência de cada dado digitado.
*/
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char * argv[]){
    
    int barras, valores, valor_leitura;  
    //Declarando as variáveis inteiras: barras (número de barras), valores (quantidade de valores a serem digitador) e 
    //valor_leitura (valor que será contabilizado e veriricado sua frequência).

    scanf ("%d", &barras);  //Recebendo inputs do teclado da quantidade de barras e a quantidade de valores.
    scanf ("%d", &valores);
    

    //Declarando um ponteiro do tipo inteiro, que será um endereço da heap, em que será armazenado um vetor terá um tamanho do número de barras
    //e que conterá em cada posição a frequancia de cada valor digitado.
    int* vetor;
    vetor = (int *)calloc(barras,sizeof(int));

    //Na iteração é recebido um valor, sendo que uma posição do vetor correspondente ao valor será acrescido em 1, indicando no final, a quantidade
    //de vezes que o número desta posição apareceu.
    //VETOR DE FREQUÊNCIA
    for (int i = 0; i < valores; i++){
        scanf ("%d", &valor_leitura);
        vetor[valor_leitura] += 1;
    }

    //A cada posição da barra será feita uma repetição, na qual até que k chegue no valor de vetor[posição i] será impresso o caractere #.
    for (int i = 0; i < barras; i++){
        printf ("%d - ", i);
        for (int k = 0; k < vetor[i]; k++){
            printf ("#");
            }
        printf ("\n");
    }
    
    free (vetor); //Desalocando, finalmente, o vetor na memória Heap.

    
    
    
    return 0;
}