/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    Curso : Bacharelado em Ciências de Computação

    Programa: CORRA PARA A BASE

    Aluno : Bernardo Marques Costa
    Número USP : 11795551

   O programa receberá uma matriz, correspondente ao mapa de um jogo (contendo seguidos 0 e com apenas um 1 correspondente 
   a base deste mapa).
   Dado as coordenadas do personagem, seu atributo de movimento e a posição da base, será necessário descobrir se este
   sobreviverá ou não:
            -> 'Game Over!' :  A distancia do personagem até sua base é maior que seu atributo de movimento.
            -> 'Voce escapou!' : A distancia é inferior.

*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/*
    Função distanciaFunction:
    Recebe os parâmentros por valor: x -> coordenada x do personagem 
                                     y -> coordernada y do personagem   
                                     bx -> coordenada x da base
                                     by -> coordenada y da base
    Calcula a distancia d, utilizando a distancia euclidiana.                      
*/
float distanciaFunction(const int x,  const int y, const int bx, const int by){
    float d = sqrt(pow(x - bx, 2) + pow(y - by, 2));
    return d;
}


int main(int argc, char *argv[]){
    
    // Declaração e leitura das variáveis N e M, correspondentes ao número de linhas e de coluna da matriz, respectivamente.
    int N, M;
    scanf("%d %d", &N, &M);

    // Alocando na memória Heap a matriz que representa o mapa do jogo.
    int **matriz = (int**)calloc(N,sizeof(int*));
    for (int i = 0; i < N; i++){
        matriz[i] = (int*)calloc(M,sizeof(int));
    }
    // Declaração e leitura das variáveis x, y e moviment:
    // x -> coordenada x do personagem. y -> coordenada y do personagem .movimente -> float correspondente ao atributo de 
    // movimento do personagem
    int x, y;
    float moviment;
    scanf("%d %d %f", &x, &y, &moviment);
    
    // Declarando as coordenadas (x,y) da base.
    int base_x, base_y;
    // Lendo os inputs correspondentes ao mapa.
    for (int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            scanf("%d", &matriz[i][j]);      
            // Quando o input dado for correspondente à 1 (ou seja, a base) teremos então a atribuição das coordenadas.
            if (matriz[i][j] == 1){
                base_x = i;
                base_y = j;
            }
        }
    }
    
    //Declarando a variável float 'distance' e atribuindo a ela o retorno da função distanciaFunction.
    float distance;
    distance = distanciaFunction(x, y, base_x, base_y);

    // Caso a distancia seja maior que a propriedade de velocidade / movimento do personagem, teremos Game Over
    // Caso contrário, o jogador sobreviverá.
    if (distance > moviment) printf("Game Over!\n");
    else printf("Voce escapou!\n");

    // Liberando a memória Heap.
    for (int i = 0; i < N; i++){
        free(matriz[i]);
    }
    free(matriz);
    
    return 0;
}