/*
    DETERMINANTE
    ALUNO: Bernardo Marques Costa
    NÚMERO USP: 11795551

    Programa que receberá um número equivalente as linhas e outro as colunas de uma matriz, verificando se é impossível calcular seu determinante
    ou se é possível, sendo uma matriz quadrada. Sendo possível, calcular este determinante.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    
    int linhas, colunas, determinante;

    scanf ("%d %d", &linhas, &colunas);  //Recebendo do teclado o número de linhas e de colunas da matriz.

    //Condicional: caso a matriz não seja quadrática (número de linhas sendo diferente do número de colunas) ou o número de linhas e/ ou de colunas
    //sejam maiores que 3, os valores de entradas serão invalidados.
    if (linhas != colunas || linhas > 3 || colunas > 3){
        printf ("Entradas invalidas");
        }

    else{
        int** matriz;


        //Alocando na memória Heap, com a função calloc, um ponteiro duplo do tipo int,
        //O ponteiro duplo está na Stack e armazena o primeiro endereço na Heap no qual inicia a contagem das linhas da matriz
        matriz = (int**) calloc(linhas, sizeof(int *));  
        
        //O laço de repetição a seguir aloca espaços na memória Heap para cada valor de coluna, armazenando no endereço de cada linha
        //o endereço de onde inicia-se a contagem das colunas, completando assim uma queda do ponteiro duplo, para simples e finalmente 
        //para a variável inteira. 
        for (int i = 0; i < colunas; i++){
            *(matriz + i) = (int*) calloc(colunas,sizeof(int));
        }

        //Preenchendo a matriz com valores enviador pelo teclado.
        for (int i = 0; i < linhas; i++){

            for (int j = 0; j < colunas; j++){

                scanf("%d", &*(*(matriz + i) + j));
            }
        }

        //Condicional por switch case:
        //Caso a matriz seja de tamanho 1, 2 ou 3 teremos os respectivos cálculos de seus determinantes.
        switch(linhas){

            case 1 : {
                determinante = matriz[0][0];
                break;
            } 
            case 2 : {
                determinante = (matriz[0][0] * matriz[1][1]) - (matriz[1][0] * matriz[0][1]);
                break;
            }
            
            case 3 : {
                determinante = matriz[0][0] * matriz[1][1] * matriz[2][2] + matriz[0][1]*matriz[1][2]*matriz[2][0] + matriz[0][2]*matriz[1][0]*matriz[2][1]
                               - matriz[2][0]*matriz[1][1]*matriz[0][2] - matriz[2][1]*matriz[1][2]*matriz[0][0] - matriz[2][2]*matriz[1][0]*matriz[0][1];
                break;
                }
            }
            
    //Imprimindo o determinante da matriz de acordo com o cálculo feito acima e a ordem desta matriz.
    printf ("O determinante da matriz de entrada equivale a %d e tem ordem %d", determinante, colunas);
    
    }
    
    
    return 0;
}