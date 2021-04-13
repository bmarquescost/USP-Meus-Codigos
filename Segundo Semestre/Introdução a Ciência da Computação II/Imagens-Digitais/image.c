/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    BCC - Bacharelado em Ciências de Computação

    Introdução a Ciência de Computação II
    Professor: Moacir Ponti

    Aluno: Bernardo Marques Costa
    Número USP: 11795551
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void cria_pgm(unsigned char **matriz, int N, char *pgm_nome) {
    FILE *pgm_handle = fopen(pgm_nome, "w");

    fprintf(pgm_handle, "P2 \n");
    fprintf(pgm_handle, "%d %d \n", N, N);
    fprintf(pgm_handle, "255 \n");
  
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) 
            fprintf(pgm_handle, "%d ", matriz[i][j]);
    
        fprintf(pgm_handle, "\n");
    }

    fclose(pgm_handle);
}

void solucao_recursiva(unsigned char **m, int tamanho_matriz, int T, int linha, int coluna, unsigned char p) {
    // Caso base: bordas da matriz
    if(linha >= tamanho_matriz || coluna >= tamanho_matriz || coluna < 0 || linha < 0)
        return;

    unsigned char *v = &(m[linha][coluna]);
    unsigned char delta_m = abs(*v - p);
    
    if(delta_m > T || delta_m == 0)
        return;
    
    *v = p;

    // Cima
    solucao_recursiva(m, tamanho_matriz, T, linha - 1, coluna, p);
    // Direita
    solucao_recursiva(m, tamanho_matriz, T, linha, coluna + 1, p);
    // Baixo
    solucao_recursiva(m, tamanho_matriz, T, linha + 1, coluna, p);
    // Esquerda
    solucao_recursiva(m, tamanho_matriz, T, linha, coluna - 1, p);
}

/*
    N -> Tamanho da matriz quadrada (N x N)
    x -> Posição da linha   
    y -> Posição da coluna
    T -> seed para rand
*/
int main(int argc, char *arv[]) {
    int N, x, y, T;

    scanf("%d %d %d %d", &N, &x, &y, &T);
    
    srand(T);

    unsigned char **matriz = calloc(N, sizeof(unsigned char *));
    
    for(int i = 0; i < N; ++i)
        matriz[i] = calloc(N, sizeof(unsigned char));

    for(int i = 0; i < N; ++i) 
        for(int j = 0; j < N; ++j) 
            matriz[i][j] = rand() % 256;


    for(int i = 0; i < N; ++i) { 
        for(int j = 0; j < N; ++j) 
            printf("%d\t", matriz[i][j]);
        printf("\n");
    }
    printf("\n");

    cria_pgm(matriz, N, "original.pgm");

    solucao_recursiva(matriz, N, T,  x - 1, y, matriz[x][y]);
    solucao_recursiva(matriz, N, T,  x, y + 1, matriz[x][y]);
    solucao_recursiva(matriz, N, T,  x + 1, y, matriz[x][y]);
    solucao_recursiva(matriz, N, T,  x, y - 1, matriz[x][y]);

    for(int i = 0; i < N; ++i) { 
        for(int j = 0; j < N; ++j) 
            printf("%d\t", matriz[i][j]);
        printf("\n");
    }
    
    // Criando pgm    
  
    cria_pgm(matriz, N, "aleatorio.pgm");


    for(int i = 0; i < N; ++i)
        free(matriz[i]);
    free(matriz);

    return 0;
}