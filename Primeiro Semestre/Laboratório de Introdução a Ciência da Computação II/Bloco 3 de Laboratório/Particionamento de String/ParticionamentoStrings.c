/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    Curso : Bacharelado em Ciência de Computação

    Programa : PARTICIONAMENTO DE STRING

    Aluno : Bernardo Marques Costa
    Número USP : 11795551

    Programa que receberá uma frase e deverá particioná-la, mostrando em cada linha cada palavra que compôe a frase.
    A ordem de impressão seguirá a seguinte regra (escolhida por entradas de valor 1 ou 2):
                1 -> ordem da prase
                2 -> ordem lexicográfica (alfabética)

*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
    Função readline:
    Recebe como parâmetro o stdin.
    Retorna um ponteiro para a cadeia de caracteres completa dada pelo input.
*/
char *readline(FILE *stream){
    char *string = NULL;
    int pos = 0;
    do{
        string = (char*)realloc(string, pos+1);
        string[pos] = (char) fgetc(stream);
        pos++;
    } while(string[pos-1] != '\n' && string[pos-1] != '\r' && !feof(stream));
    string[pos-1] = '\0';
    return string;
}

/*
    Função creatematrix:
    Recebe como parâmetros a frase completa (*s), o endereço de uma matriz para preenchê-la, e o número de palavras na frase.
    Cada linha dessa matriz corresponde a uma palavra.
*/
void creatematrix(char *s, char** m, int count){
    int spos = 0;       // spos -> posição do 'cursor' na frase completa 
    int coppy = 0;      // coppy -> index indentificando qual palavra esta sendo analisada
    int mpos = 0;       // mpos -> posição do 'cursor' na palavra, sendo retornada a 0 ao passar para a próxima linha (próxima palavra)
                        // da matriz.

    // Laço que ocorre até ser antigido o número total de palavras a serem particionadas.                  
    while(coppy < count){
        // Laço de repetição interno que faz a cópia dos caracteres da frase inicial até que encontre o espaço o final da frase
        // sendo atribuido a matriz.
        while(s[spos] != ' ' && s[spos] != '\0'){
            m[coppy] = (char*)realloc(m[coppy], mpos+1);
            m[coppy][mpos] = s[spos];
            spos++;
            mpos++;
        }
        // Acrescentado o final da string.
        m[coppy][mpos] = '\0';

        // Reiniciando o 'cursor'.
        mpos = 0;

        // Acrescentando 1 unidade a spos e a coopy, já que o 'cursor' saí do último laço na posição do espaço
        // e é necessário iniciar a análise e cópia da próxima palavra.
        spos ++;
        coppy ++;
    }
    
}

/*  
    Função justprint:
    Recebe como parâmetro a matriz ja cridada, o número de palavras e a opção desejada ( 1 ou 2).
    Apenas realiza a impressão na tela das palavras.
*/
void justprint(char **m, int n, int selector){
    int i = 0, j = 0;

    // Segundo os casos testes do programa, é necessário converter para minusculo os caracteres anteriormente maíusculos da 
    // palavras na matriz, portanto o laço a seguir realiza esse processo, subtraindo 32 do valor da tabela ASCII do caractere
    // analisado caso este esteja entre os valores de carctere maíusculo
    if(selector == 2){ 
        for (i = 0; i < n; i++){
            j = 0;
            while(m[i][j] != '\0'){
                if (m[i][j] >= 'A' && m[i][j] <= 'Z') m[i][j] = (char) m[i][j] + 32;
                j++;
            }
        }   
    }
    
    // Imprimindo as palavras.
    for (int i = 0; i < n; i++) printf("%s\n", m[i]);
}

/*
    Função alphasort:
    Recebe como parâmetro a matriz e o número de palavras contabilizados na frase inicial.
    Realiza a ordenação pelo critério lexicográfico por meio da função strcasecmp (desconsiderando a diferença de maiúscula e minúsculas).
*/
void alphasort(char **m, int n){

    int start = 0;     // Inicializando o começo da analise como 0.
    int end = n - 1;   // Inicializando o final da analise como o total de palavras -1.
    int boolean = 1;   // Flag que indicará se a lista analisada esta ou não ordenada.
    char *aux = NULL;  // Ponteiro auxiliar para a realização do swap.
    
    // Cocktail sort
    while(boolean){
        boolean = 0;  // Reiniciando a flag para os próximos ciclos.
       
        // Repetição que analisa duas palavras por vez, invertendo suas posições na lista quando a função strcasecmp retornar
        // valor > 0, indicando que a palavra anterior é 'maior' lexicograficamente que a seguinte na lista. 
        for(int i = start; i < end; i++){
            if (strcasecmp(m[i], m[i+1]) > 0){
                // Swap:
                aux = m[i+1];
                m[i+1] = m[i];
                m[i] = aux;
                boolean = 1;    // Indicando a ocorrencia do swap.
            }
        }
        // Caso a lista ja esteja ordenada.
        if (!boolean) break;
        
        // A última posição ja esta ordenada corretamente apos o último laço
        end -= 1;

        boolean = 0;  // Reiniciando a flag para o próximo laço.

        // Repetição que ocorre do final para o começo, realizando a mesma análise efetuada na repetição anterior
        for(int i = end; i >= start; i--){
             if (strcasecmp(m[i], m[i+1]) > 0){
                aux = m[i+1];
                m[i+1] = m[i];
                m[i] = aux;
                boolean = 1;
            }
        }
        // A primeira posição estará ordenada após o termino do laço anterior. 
        start += 1;
    }
}



int main(int argc, char *argv[]){
    
    char *sentence = NULL;          // Declarando e recebendo da função readline a frase completa que será particionada.
    sentence = readline(stdin);
    
    // Declarando inteira a varíavel de escolha do metodo de impressão, e recebendo-o.
    int choice;
    scanf("%d%*c", &choice);
    
    // Contando o número de palavras que há na frase inicial.
    // Para cada espaço encontrado, uma unidade será acrescida para o contador de palavras nwords
    // Como no final da frase há um '\0' e não um último espaço, teremos que acrescer mais uma unidade ao final do laço,
    // para contabilizar a última palavra.
    int nwords = 0;
    for (int i = 0; i < strlen(sentence); i++){
        if (sentence[i] == ' ') nwords++;
    } 
    nwords++;

    // Criando e alocando dinamicamente a matriz de palavras, sendo atribuido NULL para todos ponteiros que armazenarão
    // o endereço de cada palavra na Heap (isto é feito para que seja possível a utilização da função realloc).
    char **wordsmatrix;
    wordsmatrix = (char**)calloc(nwords, sizeof(char*));
    for(int i = 0; i < nwords; i++) wordsmatrix[i] = NULL;
    

    // Criando a matriz utilizando a função creatematrix.
    creatematrix(sentence, wordsmatrix, nwords);

    free(sentence); // Desalocando e liberando a memória Heap utilizada para armazenar a frase, e que não será mais utilizada.
    
    // Redirecoinado para as funções que correspondem a escolha de metodo de impressão na tela.
    if (choice == 1) justprint(wordsmatrix, nwords, choice);
    else if (choice == 2) {
        alphasort(wordsmatrix, nwords);
        justprint(wordsmatrix, nwords, choice);
    }   
    
    // Liberando a memória Heap utilziada para a criação da matriz de palavras.
    for (int i = 0; i < nwords; i++)  free(wordsmatrix[i]);
    free(wordsmatrix);

    return 0;
}