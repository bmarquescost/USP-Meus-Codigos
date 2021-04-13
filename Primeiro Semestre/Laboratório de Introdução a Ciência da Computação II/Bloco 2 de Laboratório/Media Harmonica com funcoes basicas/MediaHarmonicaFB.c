/*
    MEDIA HARMONICA AMORTIZADA COM FUNÇOES BÁSICAS
    ALUNO: Bernardo Marques Costa
    NÚMERO USP: 11795551

*/
#include <stdio.h>
#include <stdlib.h>

//Função readInt que não receberá parâmetro, retornando o valor, correspondente ao número de trabalhos que serão contabilizados.
int readInt(){
    int valor;
    scanf ("%d", &valor);
    return valor;
}


//Função readDouble que será chamada um número de vezes igual ao número de trabalhos.
//A cada chamada ela retornará uma nota que será lida nesta função.
double readDouble(){
    double nota;
    scanf("%lf", &nota);
    return nota;
}

//Função printDouble que servirá para impriminar na tela o resultado da media final.
double printDouble(double Val){
    printf ("%.2lf", Val);
    return 0;
}

int main (int argc, char* argv[]){

    int trabalhos = readInt();              //Declarando trabalhos como inteiro e chamando a função readInt que retornará o número de trabalhos digitados na função.
    double *notas;                          //Declarando um ponteiro do tipo double que servirá para armazenar o endereço na heap de uma lista de elementos do tipo double.
    double denominador = 0, media_final;        //Declarando denominador e media_final como dobule que servirão para o cálculo final da media que será impressa na função printDouble.

    notas = (double *)calloc(trabalhos, sizeof(double));
    //Notas recebe o endereço inicial na memória heap de um conjunto alocado equivalente à trabalhos (numero de trabalhos) * 8 bits --> Aqui serão armazenadas todas as notas.
    //Calloc também inicializa todas posições da memória com 0.

    //Iteração que ocorrerá da seguinte forma: para cada trabalho (que é digitado na função readInt), notas[i] (notas na posição i) receberá o retorno da função readDouble
    //A cada iteração também é acrescentado ao denominador, inicializado com 0, 1/(T + 1), equivalente a formula como 1 sobre T + 1, sendo T equivalente a nota do trabalho (que está armazenado na posição i).
    for (int i = 0; i < trabalhos; i++){
       *(notas + i) = readDouble();
       denominador += 1/(*(notas + i) + 1);
    }

    //A media final é calculada a partir da divisão do número de trabalhos pelo denominador total subtraindo em 1 o quociente. 
    media_final = (trabalhos/denominador) - 1;
    
    //A media final é enviada como parâmetro para a função printDouble.
    printDouble(media_final);

    free (notas); //liberando a memória heap utilizada.

    return 0;
    
}