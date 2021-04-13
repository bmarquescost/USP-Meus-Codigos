/*
    COMPARANDO PALAVRAS
    ALUNO: Bernardo Marques Costa
    NÚMERO USP: 11795551

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define N 100

/*
Função que compara as palavras a partir de seu tamanho, utilizando a função strlen().
*/
int tamanho(char *palavra1, char *palavra2){
    int valor;
    long int tamanho1, tamanho2;
    tamanho1 = strlen(palavra1);
    tamanho2 = strlen(palavra2);

    if (tamanho1 > tamanho2) valor = 1;       //Definindo valor para caso da palavra1 ser maior que a palavra2.
    else if (tamanho2 > tamanho1) valor = 2;  //Definindo valor para caso da palavra2 ser maior que a palavra1.
    else valor = 0;                           //Definindo valor para caso de terem tamanhos iguais.
    return valor;
}

/*
Fução que irá considerar a ordem alfabética das palavras a partir da função da bilbioteca ctype.h strcasecmp.
como a função retorna x < 0 caso palavra2 seja alfabeticamente menor que a palavra1, x > 0 para o caso oposto 
e 0 para o caso de serem identicas, temos que fazer os ajustes finais.
*/ 
int alfabetica(char *palavra1, char *palavra2){
    int valor = 0;
   
    if (strcasecmp(palavra1, palavra2) == 0) valor = 0;
    else if (strcasecmp(palavra1, palavra2) > 0) valor = 2;
    else if (strcasecmp(palavra1, palavra2) < 0) valor = 1; 
    
    return valor;
}

/*
Função que verifica a soma de cada um dos elementos de acordo com seus respctivos correspondentes numéricos na tabela
ASCII, subtraindo o valor de 97 para que A ou a sejam equivalentes à 0.
*/
int soma(char *palavra1, char *palavra2){
    long int valor, somaP1 = 0 , somaP2 = 0;

    for (int i = 0; i < strlen(palavra1); i++){
        somaP1 += tolower (palavra1[i]) - 97;    //tolower -> padronizando para minúsculo
    }
    for (int j = 0; j < strlen(palavra2); j++){
        somaP2 += tolower(palavra2[j]) - 97;
    }
    if (somaP1 > somaP2) valor = 1;
    else if (somaP2 > somaP1) valor = 2;
    else if (somaP1 == somaP2) valor = 0;
    
    return valor;
}

/*
Função que verifica a repetição de uma letra escolhida em cada uma das palavras.
*/
int repeticao (char *palavra1, char *palavra2){
    char letra_escolhida;
    long int repeticaoP1 = 0, repeticaoP2 = 0;
    int valor;

    scanf (" %c", &letra_escolhida);

    letra_escolhida = toupper(letra_escolhida);  //padronizar para maiúsculo.

    for (int i = 0; i < strlen(palavra1); i++){
        if (letra_escolhida == toupper(palavra1[i])) repeticaoP1 += 1;  //Caso a letra da palavra seja correspondente à letra escolhida, acrescenta-se 1 a variável repeticaoP1.
    }
    for (int j = 0; j < strlen(palavra2); j++){
        if (letra_escolhida == toupper(palavra2[j])) repeticaoP2 += 1;  //Caso a letra da palavra seja correspondente à letra escolhida, acrescenta-se 1 a variável repeticaoP2.
    }
    
    //Comparando os resultados obtidos pelas iterações. 
    if (repeticaoP1 > repeticaoP2) valor = 1;
    else if (repeticaoP2 > repeticaoP1) valor = 2;
    else valor = 0;
    
    return valor;
}

/*
Função que verifica qual das palavras apresenta primeiro uma letra escolhida.
*/
int primeiro (char *palavra1, char *palavra2){
    char letra; 
    int posi1 = 0, posi2 = 0, valor = 0, tamanho1, tamanho2;

    scanf (" %c", &letra);

    //Para verificar onde, em cada iteração, iremos inicializar as variáveis de iteração, verifica-se o tamanho de cada palavra.
    tamanho1 = strlen(palavra1);  
    tamanho2 = strlen(palavra2);  
    
    letra = tolower(letra); //Para que seja padronizada a letra como minúscula.
    
    int i, j;
    
    /*
    As duas iterações a seguir funcionarão da seguinte forma: do final para o começo da palavra, uma variavel posiX (sendo x = 1 para a palavra
    1 e x = 2 para palavra2) receberá a posição da string onde é encontado uma letra igual a letra escolhida pelo usuário + 1 unidade, para que não
    seja confundido posteriormente com 0 -> quando não encontra a letra dentro da cadeia de caracteres.
    */
    for(i = tamanho1 -1; i >= 0; i--){    
        if (tolower(palavra1[i]) == letra){
            posi1 = i + 1;        
            }
    }

    for(j = tamanho2 -1; j >= 0; j--){
        if (tolower(palavra2[j]) == letra){
            posi2 = j + 1;
        }
    }

    //Comparando os resultados obtidos e retornando valor para a função main.

    if (posi1 > posi2) valor = 2;
    else if (posi2 == posi1) valor = 0;
    else valor = 1;

    return valor;
}


int main(){
    int op, resposta;                                 //Declarando as variáveis op e resposta, que serão respectivamente a escolha da operação e solução do problema
    char palavra1[N] = {0}, palavra2[N] = {0};        //Declarando as cadeias de caracteres e inicalizando-as com '\0'.
    scanf ("%d", &op);                               
    scanf ("%s", palavra1);
    scanf ("%s", palavra2);
    if (op == 1) resposta = tamanho(palavra1, palavra2);        //Redirecionando para a função tamanho, enviando os parametros palavra1 e palavra2, além de retornar da função um valor que sera armazenado em resposta.
    if (op == 2) resposta = alfabetica(palavra1, palavra2);     //Redirecionando para a função alfabetica, enviando os parametros palavra1 e palavra2, além de retornar da função um valor que sera armazenado em resposta.
    if (op == 3) resposta = soma(palavra1, palavra2);           //Redirecionando para a função soma, enviando os parametros palavra1 e palavra2, além de retornar da função um valor que sera armazenado em resposta.
    if (op == 4) resposta = repeticao(palavra1, palavra2);      //Redirecionando para a função repeticao, enviando os parametros palavra1 e palavra2, além de retornar da função um valor que sera armazenado em resposta.
    if (op == 5) resposta = primeiro(palavra1, palavra2);       //Redirecionando para a função primeiro, enviando os parametros palavra1 e palavra2, além de retornar da função um valor que sera armazenado em resposta.
   
   //Imprimindo a solução final da operação escolhida.
    printf ("%d", resposta);
    return 0;
}