/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    Curso : Bacharelado em Ciências de Computação

    Programa : ADICIONANDO SOBRENOMES

    Aluno : Bernardo Marques Costa
    Número USP: 11795551

    Programa que receberá uma lista de nomes até que seja digitado o caractere '$', indicando o final dos inputs.
    A partir de obtido os nomes completos, o último sobrenome dos nomes que possuem index pares no vetor de nomes obtidos,
    isto é -> elementos [0], [2], [4] ...
    devem "emprestar" seu sobrenome para o próximo nome da lista, acrescentando-o ao final do nome seguinte.
    último sobrenome do [0] -> acrescentado ao nome de [1] (caso exista).

*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/*
    Função readname:
    Recebe como parâmetros FILE *stream (stdin) e uma flag (recebida por referência), que será utilizada para indicar o 
    termino dos inputs, ao detectar o caractere '$'.
    Retorna a string completa, sendo construida até que seja identificado o enter ('\n').
    
*/
char *readname(FILE *stream, int *flag){
    char *string = NULL;        // String que será retornada.
    int pos = 0;                // Variável de controle da posição na string.
    
    // Laço de repetição que ocorre até que seja encontrado '\n', '\r' ou seja o final do arquivo. 
    do{     
        string = (char*)realloc(string, pos+1);         // Realocação do vetor na Heap, para alocar mais espaço e armazenar os caracteres 
        string[pos++] = fgetc(stream);                  // Capturando do buffer os caracteres digitados
        
        // Detectando o indicador de final do input e declarando a flag como 1.
        if(string[pos-1] == '$') *flag = 1;

    }while(string[pos-1] != '\n' && string[pos-1] != '\r' && !feof(stream));

    // Caso a flag seja 1, teremos que realocar e 1 posição a menos e acrescentar o indicador de final de string 2 posições anteriores.
    if (*flag == 1) {
        string = (char*)realloc(string, pos-1);
        string[pos-2] = '\0';
    }

    else string[pos-1] = '\0';
    return string;
}

/*
    Função addlastname:
    Recebe como parâmetro a matriz de nomes e o inteiro correspondente a posição analisada do vetor.
    Realiza o acrescimo do último sobrenome da posição de valor par, no nome de indice impar.
*/
void addlastname(char **names, int i){
    int j = strlen(names[i]);      
    int poslastname = 0;
    
    // Do final para o começo do nome da posição par, será iterado até que se encontre a posição em que começa o último sobrenome
    while(names[i][j] != ' '){
        poslastname = j;
        j--;
    }
    
    // Adicionando espaço no nome de indice impar.
    int counter = strlen(names[i+1]);
    names[i+1][counter++] = ' ';
    
    int aux = poslastname;
   
    // Até que seja encontrado o final do nome de indice par, iremos realocar o nome no indice impar e acrescentar na posição
    // o caractere correspondente as posições que serão iteradas no último sobrenome. 
    while(names[i][aux] != '\0'){

        names[i+1] = (char*)realloc(names[i+1], counter+1);
        names[i+1][counter] = names[i][aux];
        aux++;
        counter++;
    }
    // Colocando o indicador de final de string.
    names[i+1][counter] = '\0';
  
}

int main(int argc, char *argv[]){

    // Declarando e alocando na Heap a matriz que armazenará todos os nomes.
    char **allnames = (char**)calloc(1,sizeof(char*));
    allnames[0] = NULL;
    
    int ncount = 0;  // inteiro que irá contabilizar o número de nomes.
    int flag = 0;

    // Repetição que ocorre até que a flag (alterada para 1 quando identificar '$')
    // Para cada iteração, teremos uma realocação da matriz, sendo cada linha associada a um nome.
    while(!flag){
        allnames = (char**)realloc(allnames, (ncount+1)*sizeof(char*));
        allnames[ncount] = readname(stdin, &flag);
        ncount++;
    }
    
    // Até que i seja igual ao número de nomes - 1, teremos o acrescimo do sobrenome para cada i de valor par no nome equivalente a i+1.
    for(int i = 0; i < ncount-1; i++){
        if (i%2 == 0) addlastname(allnames, i);
    }
    
    // Printando os nomes.
    for(int i = 0; i < ncount; i++) printf("%s\n", allnames[i]);
    
    // Liberando a memória Heap utilizada.
    for (int i = 0; i < ncount; i++) free(allnames[i]);
    free(allnames);

    return 0;
}