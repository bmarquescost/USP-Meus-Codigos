/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    Curso : Bacharelado em Ciências de Computação

    Programa : PADDING DE IMAGENS

    Aluno : Bernardo Marques Costa
    Número USP: 11795551

    O programa deverá receber as dimensões de uma matriz e seus elementos, em seguida, um inteiro correspondente ao tamanho
    da borda (correspondente ao tamanho do padding que será realizado na matriz).
    Deverá então construir a matriz com a borda e printar a matriz resultante e a inicial logo em seguida.

*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int **inputmatriz = NULL;  // Declarando a matriz inicial que corresponderá a imagem que será alterada. 
    int width, height;         // Declarandoa  largura e a altura da matriz inicial.
    int paddsize;              // Declarando o inteiro correspondente ao tamanho da borda
    
    scanf("%d %d", &width, &height);

    // Alocando dinamicamente as linhas da matriz
    inputmatriz = (int**)calloc(height, sizeof(int*));
    int i, j;
    // Alocando dinamicamente as colunas da matriz                   
    for (int i = 0; i < height; i++) inputmatriz[i] = (int*)calloc(width, sizeof(int));
    
    // Recebendo os elementos da matriz. 
    for (i  = 0; i < height; i++){
        for (j = 0; j < width; j++){
            scanf("%d", &inputmatriz[i][j]);
        }
    }

    scanf("%d", &paddsize);
    
    // Declarando as novas dimensões da matriz.
    int newheight = 2*paddsize + height;
    int newwidth = 2*paddsize + width;

    // Declarando a matriz resultante e alocando dinamicamente suas novas dimensões
    int **paddedmatriz;
    paddedmatriz = (int**)calloc (newheight, sizeof(int*));
    for (i = 0; i < newheight; i++) paddedmatriz[i]  = (int*)calloc(newwidth, sizeof(int));

    // A iteração irá alterar os elementos correspondentes ao meio da matriz resultante, colocando os elementos da matriz
    // inicial de entrada.
    for (i = 0; i < height; i++){
        for (j = 0; j < width; j++){
            paddedmatriz[i+paddsize][j+paddsize] = inputmatriz[i][j];
        }
    }

    // Imprimindo o resultado na formatação desejada.
    for (i = 0; i < newheight; i++){
            for (j = 0; j < newwidth; j++){
                    if (j == newwidth - 1) printf("%d", paddedmatriz[i][j]);
                    else printf("%d ", paddedmatriz[i][j]);
            }
            printf("\n");   
    }
    printf("\n");

    // imprimindo a matriz inicial na formatação desejada.
    for(i = 0; i < height; i++){
        for (j = 0; j < width; j++){
            
            if (j == width - 1) printf("%d", inputmatriz[i][j]);
            
            else printf("%d ", inputmatriz[i][j]);
        }
        printf("\n");
    }

    
    // Desalocando a memória Heap utilizada para armazenar as matrizes.

    for (i = 0; i < height; i++) free(inputmatriz[i]);
    free(inputmatriz);
    
    for (i = 0; i < newheight; i++) free(paddedmatriz[i]);
    free(paddedmatriz);

    return 0;
}