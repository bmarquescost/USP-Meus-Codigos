/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    Curso : Bacharelado em Ciências de Computação

    Programa : TROCANDO SOBRENOMES

    Aluno : Bernardo Marques Costa
    Número USP: 11795551

    Programa que deverá ler nomes completo e realizar a troca de sobrenomes entre os nomes que se encontram em posições
    simétricas vetor.
*/

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char *readline(FILE *stream, int *flag);    
void makethetrade(char **names, int ncount, int trade);

int main(int argc, char *argv[]){

    char **names = NULL;        // Matriz de nomes
    int wordcounter = 0;        // Número total de nomes 
    int flag = 1;               // indicará a existencia do '$', correspondente ao elemento de parada.
    
    // Realocação e entrada dos nomes.
    while(flag){
        names = (char**)realloc(names, (wordcounter+1)*sizeof(char*));
        names[wordcounter] = readline(stdin, &flag);
        wordcounter++;
    }

    // Laço que ocorre até o metade do número de palavras:
    // -> Se for impar, o elemento do meio não mudará o sobrenome, não tendo par para fazer a troca.
    // -> Se for par, os elementos intermediários farão a troca de sobrenomes entre sí.
    for (int i = 0; i < wordcounter/2; i++){
        makethetrade(names, wordcounter, i);
    }

    // Printado o resultado,
    for (int i = 0; i < wordcounter; i++){
        printf("%s\n", names[i]);
    }

    // Desalocando a memória Heap utilizada.
    for (int i = 0; i < wordcounter; i++) free(names[i]);
    free(names);


    return 0;
}


/* 
    Função readline:
    Recebe como parâmetro o stdin e o endereço da flag.
    Retorna um ponteiro para uma string na memória Heap
*/
char *readline(FILE *stream, int *flag){
    char *string = NULL;
    int pos = 0;
    do {
        string = (char*)realloc(string, pos+1);
        string[pos++] = fgetc(stream);
        if (string[pos-1] == '$') *flag = 0;    // Caso a flag '$' seja encontrada, significa que devemos parar a leitura.
   
   } while(string[pos-1] != '\n' && string[pos-1] != '\r' && !feof(stream));
    
    string[pos-1] = '\0';
    // Realocando o último nome para que não finalize com o caractere '$'.
    if (!*flag){
        string = realloc(string, pos-1);
        string[pos-2] = '\0';
    }

    return string;
}


/*
    Função makethetrade:
    -> Realiza a troca dos sobrenomes.
    -> Recebe como parâmentros: a matriz de nomes (names), o número total de nomes (ncount), e o indice do vetor (trades) em 
       que se está fazendo a troca neste momentos.
*/
void makethetrade(char **names, int ncount, int trades){
    
    // Declarando os ponteiros que armazenarão o endereço na Heap de onde inicia-se a cadeia de caracteres correspondentes
    // aos sobrenomes, tanto do elemento anterior a metade do vetor quanto seu par.
    char *firstlastname = NULL;      
    char *lastlastname = NULL;

    // Declarando as variáveis para abstrair a ideia de que o primeiro nome corresponde ao elemento i (do laço for na main) -> trades enquanto
    // o seu pair (último) corresponde ao número total de nomes - 1 - i. 
    int first = trades;
    int last = ncount - trades - 1;

    // Contabilizando a posição inicial em que começa o último espaço (o que corresponde a posição em que 
    // começa o sobrenome, tanto no primeiro nome quanto no último.
    int i = strlen(names[first]);
    int spacepos1 = 0;
    while(names[first][i] != ' '){
        spacepos1 = i;
        i--;
    }

    i = strlen(names[last]);
    int spacepos2 = 0;
    while(names[last][i] != ' '){
        spacepos2 = i;
        i--;
    }
    
    // Construindo as cadeia de caracteres que correspondem ao sobrenome do primeiro e do último nome
    // Os laços while ocorrem até que não seja detectado mais um caractere alfabético (pois eventualmente poderia ser atribuido
    // lixo da memória na posião final do sobrenome).
    int pos = 0;
    int aux1 = spacepos1;
    while((names[first][aux1] >= 'A' && names[first][aux1] <= 'Z')||(names[first][aux1] >= 'a' && names[first][aux1] <= 'z')){
            firstlastname = realloc(firstlastname, pos+1);
            firstlastname[pos++] = names[first][aux1++];      
    }
    pos = 0;
    int aux2 = spacepos2;
    while((names[last][aux2] >= 'A' && names[last][aux2] <= 'Z')||(names[last][aux2] >= 'a' && names[last][aux2] <= 'z')){
        lastlastname = realloc(lastlastname, pos+1);
        lastlastname[pos++] = names[last][aux2++]; 
    }

    // Atribuindo aos nomes os sobrenomes de seu par simetrico no vetor:
    // É primeiro realizado uma realocação até o espaço, para desconsiderar o sobrenome antigo e "sobreescrever" o novo.
   
    // --> Para o primeiro nome (nome antes da metade do vetor).
    i = spacepos1;
    int counter = 0;
    while(counter < strlen(lastlastname)){
        names[first] = realloc(names[first], i+counter+1);
        names[first][counter+i] = lastlastname[counter];
        counter++;
    }
    // Realocação e acrescimo do '\0'
    names[first] = realloc(names[first], counter+i - 1);        
    names[first][counter+i] = '\0';
    

    // --> Para o último nome (nome apos a metade do vetor).
    i = spacepos2;
    counter = 0;
    while(counter < strlen(firstlastname)){
        names[last] = realloc(names[last], i+counter+1);
        names[last][counter+i] = firstlastname[counter];
        counter++;
    }
    // Realocação e acrescimo do '\0'
    names[last] = realloc(names[last], counter+i - 1);
    names[last][counter+i] = '\0';

    // Desalocando a Heap utilizada para armazenar as strings temporárias dos sobrenomes.
    free(firstlastname);
    free(lastlastname);
}