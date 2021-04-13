/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    Curso : Bacharelado em Ciências de Computação

    Programa: MATRIZ DE NOMES

    Aluno : Bernardo Marques Costa
    Número USP : 11795551

    O programa receberá 5 nomes, sendo atribuídos a uma matriz de strings e deverá orderná-la de forma a mostra
    ao final todos os nomes em ordem alfabética.

*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
    Função readline:
    Recebe como parâmetros: stdio (standard input and output).
    Retorna: string completa.
    Realiza a leitura do teclado e armazena em uma string, retornando-á.
*/
char *readline(FILE *stream){
    char *string = NULL;
    int pos = 0;
    do{
        string = (char*)realloc(string, pos+1);
        string[pos] = (char) fgetc(stream);
        pos++;
    } while(string[pos-1] != '\n' && !feof(stream));
    string[pos-1] = '\0';
    
    return string;
}

/*
    Função alphasort -> ordenação de critério alfabético.
    Recebe como parâmetro a matriz de nomes.
    Útiliza o algorítmo cocktail sort para realizar a ordenação
*/
void alphasort(char **n){
    
    int boolean = 1;   // Variável que representa uma flag, funcioando como verificador da ordenação da matriz dentro do laço.
    
    // Variáveis que armazenam o início e o final, que irão reger a ordenação dentro do laço.
    int start = 0, end = 4;
    
    // Ponteiro auxiliar que servirá como variável temporária para o processo de swap.
    char *aux = NULL;
   
    while(boolean){

        boolean = 0;  // Reiniciando o ciclo.

        // Do início (start) para o fim (end), é verificado se uma string possui valor alfabético (segundo a ordem afabética) maior
        // a seguinte -> caso seja, suas posições são trocadas e a flag é convertida em 1, indicando a ocorrencia do processo.
        //            -> caso não seja, encerra-se processo: já está ordenado o vetor.
        for (int i = start; i < end; i++){
           if (strcmp(n[i], n[i+1]) > 0){
              aux = n[i+1];
              n[i+1] = n[i];
              n[i] = aux;
              boolean = 1; 
           }
        }
       
       if (!boolean) break; // Encerrando o processo.

       // Após o anterior laço, a última posição ja está ordenada corretamente, sendo possivel desconsiderá-la 
       end -= 1;

       boolean = 0;

       // Do final (end) para o início (start), é verificado da mesma manéira que o laço anterior.
       for (int i = end; i >= start; i--){
           if (strcmp(n[i], n[i+1]) > 0){
               aux = n[i+1];
               n[i+1] = n[i];
               n[i] = aux;
               boolean = 1;
           }
       }
       // Após o último laço, a primeira posição já estará ordenada, sendo possível desconsiderá-la.
       start += 1;
    }
}

int main(int argc, char *argv[]){

    // Declarando e alocando a matriz de 5 linhas e que em cada uma delas armazenará uma string correspondente aos nomes.
    char **names = (char**)calloc(5, sizeof(char*));

    // Leitura dos nomes pela função readline.
    for (int i = 0; i < 5; i++){
        names[i] = readline(stdin);
    }

    // Utilizando a função alphasort para a ordenação
    alphasort(names);

    // Imprimindo o resultado obtido.
    for (int i = 0; i < 5; i++){
        printf("%s\n", names[i]);
    }
    
    // Liberando a memória Heap utilizada.
    for (int i = 0; i < 5; i++) free(names[i]);
    free(names);

    return 0;
}