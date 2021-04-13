/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    BCC  - Bacharelado de Ciências de Computação
    Aluno: Bernardo Marques Costa
    Número USP: 11795551

    ANÁLISE DE ALGORITMO E OTIMIZAÇÃO

    Grupo A-G 
*/ 

#include <stdio.h>
#include <stdlib.h>

/* Função recursiva */
void recursive(double **mat, int m, int i){        
    if(i >= m) return; 
    for (int j = 0; j < m; j++) { 
        if (i > j) // c - 1 
            mat[i][j]= (i+j)/2.0; 

        else if (i < j)  
            mat[i][j]= (i+j)/4.0; 
        
        else {     
            double soma = 0.0;
        
            for (int a = 0; a < m; a++)  
                if (i-1 >= 0) soma += mat[i-1][a];
                                       
            mat[i][j]= soma; 
        }
    }
    recursive(mat, m, i + 1);
}

/* Função iterativa fornecida pelo exercício proposto */
void iterative(double **mat, int m){
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {

            if (i > j) 
                mat[i][j]= (i+j)/2.0; 
            
            else if (i < j) 
                mat[i][j]= (i+j)/4.0; 
            
            else {
                double soma = 0.0;
                for (int a = 0; a < m; a++) 
                    if (i-1 >= 0) soma+= mat[i-1][a];
                
                mat[i][j]= soma; 
            }
        }
    }
}

/* 
    Função otimizada:
    
    Guarda a somatória da linha anterior em um vetor de somas, permitindo utiliza-lo ao invés de percorrer a
    mais uma linha da matriz mais uma vez. 
    Além disso, a ordem das comparações foram melhoradas para otimizar minimamente o código.
*/
void optmimus_prime_algoritm(double **mat, int m){
    
    double *sum_vec = calloc(m, sizeof(double)); 
    
    double sum = 0;
    
    for (int i = 0; i < m; ++i) {  // roda m vezes
        sum = 0;
        
        for (int j = 0; j < m; ++j) {  // roda m vezes
             
            if(i == j) { // entra 1 vez por linha - comparação
                if(i > 0) mat[i][j] = sum_vec[i-1]; //  entra para i > 0 -> comparação (se entrar: + comparação e aritmética) 
                else mat[i][j] = 0.0;              
            }

            else 
                mat[i][j] = (i+j) / ((i > j)? 2.0 : 4.0);   // entra (m - 1) vezes por linha comparação e arimética
            
            sum += mat[i][j]; // aritmética
        }
        sum_vec[i] = sum; 
    }

    free(sum_vec);
}

int main(void){
    int m;
    double **matrix = 0;
    scanf("%d", &m);

    matrix = calloc(m, sizeof(double*));
    
    for(int i = 0; i < m; i++)
        matrix[i] = calloc(m, sizeof(double));

    optmimus_prime_algoritm(matrix, m);

    for(int c = 0; c < m; ++c)
        printf("%.2lf ", matrix[m -1][c]);
    
    printf("\n");

    for(int i = 0; i < m; i++)
        free(matrix[i]);
    free(matrix);

}