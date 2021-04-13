/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    Curso : Bacharelado em Ciências de Computação

    Programa: ORDENAR REGISTROS

    Aluno : Bernardo Marques Costa
    Número USP : 11795551

    Programa que receberá um input via stdin de dados contendo diversos dados:
            -> Um inteiro que representará a operação: 1 - ordenação lexicográfica, 2 - ordenação númerica
            -> String de ilimitados caracteres seguidos de um número inteiro.
    O programa deverá ordenar e imprimir na tela o resultado da ordenação dos dados.

*/


#include <string.h>
#include <stdlib.h>
#include <stdio.h>


// A struct DATA será um tipo capaz de armazenar uma string da informação e o número inteiro que está no final de sua linha
typedef struct{
    char *infostring;
    int numeric;

} DATA;

// A struct FULL_DATA será um tipo que ajudará na organização do codigo, de forma a criar uma única varíavel que contém todas
// informações necessárias e importantes para o programa
typedef struct{
    DATA *datainput;
    int num_inputs;

} FULL_DATA;

/*
    Função readline:
    Recebe como parâmetros: stdio (standard input and output).
    Retorna: string completa.
    Realiza a leitura do teclado e armazena em uma string, retornando-á.
*/
char *readline(FILE *stream){
    char *string = NULL;
    int pos = 0;
    do {
        string = (char*)realloc(string, pos+1);
        string[pos] = (char)fgetc(stream);
        pos++;
    }while(string[pos - 1] != '\n' && string[pos-1] != '\r' && !feof(stream));
    string[pos-1] = '\0';
    
    return string;
}

/*
    Função createdata:
    Recebe como parâmentros:
        -> lineardata: recebe por referência a variável do tipo FULL_DATA que armazenará todas as informações após a conclusão
                       dessa função.
        -> information: recebe a matriz que guarda todas strings que foram digitadas (ainda na função main) a partir do stdin.
*/
void createdata(FULL_DATA *lineardata, char **information){

    char *numericinchar = NULL;  // String auxiliar temporária que armazenará a string que corresponde ao inteiro.
    
    int auxiliar = 1, wherespace = 0;    //auxiliar - variável que sofrerá acréscimo e será index de information
                                         // (a inicialização com 1 é devido ao primeiro input correspondente ao tipo de ordenação)
                                         // wherespace - variável que armazenará a posição do espaço na string completa.

    // Laço de repetição que ocorrerá até todos dados sejam copiados para os devidos campos de lineardata.                                        
    while (auxiliar < lineardata->num_inputs + 1){
        
        int i = strlen(information[auxiliar]) - 1;
        // Laço de repetição que encontrará a posição do espaço que separa a string de caracteres e o inicio dos números inteiros.
        while(information[auxiliar][i] > '9' || information[auxiliar][i] < '0') i--;
        while (information[auxiliar][i] != ' '){
                wherespace = i;
                i--; 
        }
        // Laço de repetição que constrói a string numericinchar : string de valores que correspondem ao número inteiro.
        int j = 0;
        for (i = wherespace, j = 0; information[auxiliar][i] != '\0'; i++){
            numericinchar = (char*)realloc(numericinchar, j+1);
            numericinchar[j] = information[auxiliar][i];
            j++;
        }
        numericinchar[j] = '\0';
        
        // Convertendo a string de números em ASCII para inteiros, sendo atribuído para o campo númerico de um dado na posição respectiva
        lineardata->datainput[auxiliar-1].numeric = atoi(numericinchar);

        // Construindo o vetor da informação em string.
        // O laço inicia da primeira posição da string information (k = 0) até a posição em que se encontra espaço que separa
        // a string de chars e o início do número inteiro.
        for (int k = 0; k < wherespace; k++){
            lineardata->datainput[auxiliar-1].infostring = (char*)realloc(lineardata->datainput[auxiliar-1].infostring, k+1);
            lineardata->datainput[auxiliar-1].infostring[k] = information[auxiliar][k];
        }
        lineardata->datainput[auxiliar-1].infostring[wherespace-1] = '\0';          

        auxiliar++;
    }


    // Dando free nas variáveis que utilizaram da memória Heap.
    free (numericinchar);

    // Information não será mais necessária na função main.
    for (int i = 0; i < lineardata->num_inputs +1; i++) {
        free(information[i]);
    }
    free(information);
    
}


/*
    Função alphabetically :
    Recebe como parâmetro: endereço de todos os dados (*data).
    Realiza a ordenação pelo critério lexicográfico.
*/
void alphabetically(FULL_DATA *data){

    DATA aux;  // Criando a variável aux temporária que servirá para a realização de um swap (rearranjar a ordem dos dados).

    int i, start = 0, boolean = 1; // start será variável que corresponde ao inicio da operação, sendo ajustada conforme o laço
                                   // se repete.
                                   // boolean será uma flag que indicará 0 para ordenação completa e 1 para não ordenada.

    int end = data->num_inputs - 1;  // end representará o última posição para realizar o processo de comparação.

    // COCKTAIL SORT
    // Laço de ordenação.
    while (boolean){
        boolean = 0; 

        // Do início até o fim, são rearranjadas as variáveis do tipo struct DATA de acordo com o campo da string
        // Caso uma posição seja maior que a seguinte, ocorrerá um swap.
        for (i = start; i < end; i++){
            // A função strcmp retorna um número > 0 caso a primeira string seja alfabeticamente maior que a segunda (esteja
            // depois em ordem alfabetica)
            if (strcmp(data->datainput[i].infostring, data->datainput[i+1].infostring) > 0){
                aux = data->datainput[i+1];
                data->datainput[i+1] = data->datainput[i];
                data->datainput[i] = aux;
                boolean = 1;
            }
        }
        // Caso boolean seja 0, é entendido que não ocorreu alteração no laço de repetição anterior: o vetor ja está ordernado.
        if (!boolean) break;

        boolean = 0;

        end -= 1;   // Diminuindo em 1 o final : o último elemento já está ordenado depois do laço anterior.
        
        // Laço de repetição que ocorre do final para o começo do vetor de strings.
        // A forma de operação é semelhante ao laço 'for' anterior.
        for (i = end - 1; i >= start; i--){
            if(strcmp(data->datainput[i].infostring, data->datainput[i+1].infostring) > 0){
                aux = data->datainput[i+1];
                data->datainput[i+1] = data->datainput[i];
                data->datainput[i] = aux;
                boolean = 1;
            }
        }
        start++; // Acrescendo start, pois a primeiro elemento ja está ordenado depois do último laço.
    }
}


/*
    Função numeric_ordenation:
    Recebe como parâmetro: endereço de todos os dados (*data). 
    Realiza a ordenação dos dados pelo critério númerico.
*/
void numeric_ordenation(FULL_DATA *data){
    
    DATA aux;
    int i, boolean = 1;
    int start = 0;
    int end = data->num_inputs - 1;

    // COCKTAIL SORT
    while (boolean){
        boolean = 0;
        for (i = start; i < end; i++){
            if (data->datainput[i].numeric > data->datainput[i+1].numeric){
                aux = data->datainput[i+1];
                data->datainput[i+1] = data->datainput[i];
                data->datainput[i] = aux;
                boolean = 1;
            }
        }
        if (!boolean) break;

        boolean = 0;

        end -= 1;

        for (i = end - 1; i >= start; i--){
            if(data->datainput[i].numeric > data->datainput[i+1].numeric){
                aux = data->datainput[i+1];
                data->datainput[i+1] = data->datainput[i];
                data->datainput[i] = aux;
                boolean = 1;
            }
        }
        start++;
    }
}


int main(int argc, char *argv[]){

    char **information = calloc(1,sizeof(char*));   // Matriz que será utilizada temporariamente para armazenar as entradas.
    int numberofinputs = 0;                             
    int typeordenation;

   // Realocação e leitura das entradas enquanto não é registrado o final do arquivo (feof(stdin)).
    do{
        information = realloc(information, sizeof(char*)*(numberofinputs+1));
        information[numberofinputs] = readline(stdin);
        numberofinputs++;
    }while(!feof(stdin));
    numberofinputs--;

    typeordenation = atoi(information[0]);
    
    // Declarando a variável do tipo struct FULL_DATA que armazenará todas as informações:
    //               -> possui um campo para um vetor de DADOS: que por sua vez armazena as strings e os números inteiros.
    //               -> possui um campo para o numero de inputs dados (desconsiderando a entrada correspondente ao tipo de ordenação).
    FULL_DATA inputinline;
    inputinline.num_inputs = numberofinputs;

    // Alocando inputinline.datainput na Heap com o número de inputs (desconsiderando 1 -> comando), blocos de tamanho sizeof(DATA).  
    inputinline.datainput = (DATA *)calloc(inputinline.num_inputs,sizeof(DATA));
    for (int i = 0; i < numberofinputs; i++){
        inputinline.datainput[i].infostring = NULL;  // Declarando NULL para permitir realocação
    }

    // Criando os dados em inputinline
    createdata(&inputinline, information);

    // Redirecionando para a função correspondente a operação desejada.
    if (typeordenation == 1) alphabetically(&inputinline);
    else if (typeordenation == 2) numeric_ordenation(&inputinline);

    // Impressão.
    for (int i = 0; i < inputinline.num_inputs; i++){
        printf("%d\t%s\n", inputinline.datainput[i].numeric, inputinline.datainput[i].infostring);
    }


    // Desalocando a memória Heap utilizada.
    for (int i = 0; i < numberofinputs; i++){
        free(inputinline.datainput[i].infostring);
    }
    free(inputinline.datainput);

    return 0;
}