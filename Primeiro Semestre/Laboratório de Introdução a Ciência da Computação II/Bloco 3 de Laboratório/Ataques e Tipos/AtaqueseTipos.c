/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    Curso: Bacharelado em Ciências de Computação
    
    Programa: ATAQUES E TIPOS

    Disciplina: Laboratório de Introdução a Ciência da Computação
    Aluno: Bernardo Marques Costa
    Número USP: 11795551

    Programa que analisa uma matriz que corresponde aos multiplicadores de danos de um jogo de RPG.
    Cada linha e cada coluna é um tipo, sendo cada linha o tipo do atacante e a coluna o tipo do adversário.
    Será demonstrado qual o maior dano possível e qual o indice (correpondente ao tipo do atacante). 

*/

#include <stdio.h>
#include <stdlib.h>

// Criando a struct do tipo dados que armazenará o dano e o tipo de cada entrada, de modo a facilitar a análise
typedef struct {
    float dano;
    int tipo;
} ATAQUE;

int main(int argc, char *argv[]){
    
    int numero_tipos;               // Criando o inteiro correspondente ao numero de tipos que existem.
    scanf("%d", &numero_tipos);    
    
    // Criando a matriz dos multiplicadores de danos, sendo do tipo float
    // Alocando espaço para cada linha na Heap, e posteriormente alocando cada coluna com um laço de repetição
    float **matrizdedanos;  
    matrizdedanos = (float**)calloc(numero_tipos, sizeof(float*));
    for (int i = 0; i < numero_tipos; i++){
        matrizdedanos[i] = (float *)calloc(numero_tipos, sizeof(float));
    }

    // Para cada linha será percorrida coluna a coluna, de modo a preencher a matriz.
    for (int i = 0; i < numero_tipos ; i++){
        for (int j = 0; j < numero_tipos; j++){
            scanf("%f", &matrizdedanos[i][j]);
        }
    }
    
    // Criando e alocando na memória Heap o vetor de ataques do tipo ATAQUE.
    ATAQUE *ataques;
    ataques = (ATAQUE*)calloc(numero_tipos, sizeof(ATAQUE));
    
    // inputdano será uma variável float que armazenará temporariamente cada input de dano, que será atribuida ao
    // vetor ataque em uma posição que será constantemente alterada pela variável contador.
    float inputdano;
    int contador = 0;
    
    // Laço que rodará infinitamente. Ocorrerá um break quando a entrada inputdano for igual à -1.
    while(1){
        scanf("%f", &inputdano);
        if (inputdano == -1) {
            break;
        }
        else ataques[contador].dano = inputdano;  // Atribuindo dano ao vetor
        scanf("%d", &ataques[contador].tipo);     // Lendo e atribuindo o tipo ao vetor em dada posição.
        contador++;
    }
    
    // Criando como float as variáveis melhorataque (correspondente à melhor opção de dano) e dano multiplicado
    // que será alterado constantemente.
    float melhorataque = 0, danomultiplicado;

    // Declarando inteiras as variáveis indice (correpondente ao indice do tipo que resultou em um maior dano)
    // e tipoadversário que será lido.
    int indice = 0, tipoadversario;
    scanf("%d", &tipoadversario);

    // Para cada repetição do laço anterior será feita uma conta sobre o valor do dano.
    // Ao melhordano será atribuido um danomultiplicado, sendo comparado a cada laço de repetição, de forma a 
    // obter no final o melhor dano possível e o indice do tipo.
    for (int i = 0; i < contador; i++){
        danomultiplicado = matrizdedanos[ataques[i].tipo][tipoadversario]*ataques[i].dano;
        if (danomultiplicado > melhorataque){
            melhorataque = danomultiplicado;
            indice = i;
        }
    }
    
    printf("O melhor ataque possui indice %d e dano %.2f", indice, melhorataque);

    // Desalocando a memória Heap utilizada.
    for (int i = 0; i < numero_tipos; i++){
        free(matrizdedanos[i]);
    }
    free(matrizdedanos);

    return 0;
}