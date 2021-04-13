/*
    ICMC - Instituto de Ciências Matemáticas e de Computação
    Curso : Bacharelado em Ciências de Computação

    Programa : HORÁRIOS INTERPLANETARES

    Aluno : Bernardo Marques Costa
    Número USP: 11795551

    O programa receberá um valor inteiro correspondente a segundos e em seguida o input correspondente ao nome de um planeta
    o qual deverá ser convertido os segundos.
  
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *readline(FILE *stream);

// Cabeçalho das funções
void Terra_function(long int *sec_input, int *sec, int *min, long int *hour, long int *days);
void Venus_function(long int *sec_input, int *sec, int *min, long int *hour, long int *days);
void Jupiter_function(long int *sec_input, int *sec, int *min, long int *hour, long int *days);
void Mercury_function(long int *sec_input, int *sec, int *min, long int *hour, long int *days);

int main(int argc, char *argv[]){

    long int secondsinput; // Declarando o long int que armazenará o total de segundos.    
    int seconds;           
    int minutes;
    long int hour;
    long int days;
    char *planet = NULL; // Vetor de caracteres que corresponde que receberá pelo stdin o input do planeta desejado.

    // Lendo o número de segundo e desconsiderando o caractere '\r' ou '\n' digitado para não conflitar com a função readline.
    scanf("%li%*c", &secondsinput);
    
    // Recebendo a string.
    planet = readline(stdin);

    // Redirecionando para a função de calculo dos dados de cada planeta.
    if (strcasecmp(planet, "Terra") == 0) Terra_function(&secondsinput, &seconds, &minutes, &hour, &days);
    else if (strcasecmp(planet, "Venus") == 0) Venus_function(&secondsinput, &seconds, &minutes, &hour, &days);
    else if (strcasecmp(planet, "Jupiter") == 0) Jupiter_function(&secondsinput, &seconds, &minutes, &hour, &days);
    else if (strcasecmp(planet, "Mercurio") == 0) Mercury_function(&secondsinput, &seconds, &minutes, &hour, &days);
    
    // Imprimindo o resultado.
    printf("%li segundos no planeta %s equivalem a:\n", secondsinput, planet);
    printf("%li dias, %li horas, %d minutos e %d segundos\n", days, hour, minutes, seconds);

    free(planet);

    return 0;
}


/*
    Função readline:
    Recebe a stdin como parâmetro e retorna a string completa.
*/
char *readline(FILE *  stream){
    char *string = NULL;
    int pos = 0;
    do{
        // Alocação dinamica de string.
        string = (char*)realloc(string, pos+1);
        string[pos++] = (char) fgetc(stream); // Recebendo do buffer do teclado o caractere e armazenando-o na string.
    }while(string[pos-1] != '\n' && string[pos-1] != '\r' && !feof(stream));
    string[pos-1] = '\0';
    return string;
}

/*
    Função Terra_function:
    Recebe todos os dados por referência.
    --> Calcula os segundos a partir do modulo do seguntos total por 60 -> já que é o que resta do cálculo.
    --> Calcula os minutos a partir do modulo do quociente obtido pela primeira divisão por 60.
    --> Horas corresponde ao mesmo processo, mas agora por 24 já que a cada 24 horas teríamos 1 dia.
    --> Dias, portanto é o resultado da divisão dos segundos pelo total de segundos em um dia na terra.

*/
void Terra_function(long int*sec_input, int *sec, int *min, long int *hour, long int *days){
    *sec = *sec_input % 60;
    *min = (*sec_input / 60) % 60;
    *hour = (*sec_input / 3600) % 24;
    *days = (*sec_input / 86400);
}

/*
    Função Venus_function:
    --> Calcula os segundos e os minutos da mesma forma, já que tratam-se de conceitos fixos e universais.
    --> Como cada dia em Venus equivale à 243 dias na terra : 1 dia em venus equivale à 5832 horas (243 * 24).
    --> O total de dias então é a divisão do total de segundo pelo total de segundo em um dia.
*/
void Venus_function(long int*sec_input, int *sec, int *min, long int *hour, long int *days){
    *sec = *sec_input % 60;
    *min = (*sec_input / 60) % 60;
    *hour = (*sec_input / 3600) % 5832;
    *days = (*sec_input / (3600*5832));
} 

/*
    Função Jupiter_function:
    Como temos que 1 dia em jupiter equivale a 9 horas e 56 minutos na terra, iremos inverter a análise.
    --> O número de segundos no dia é equivalente à 9*60*60 + 56*60 = 35.760 : temos então que o número de dias é equivalente
        ao número total de segundos dividido por 35.760.
    --> Como o resto da divisão acima (seu modulo) equivale ao número restante de segundos (ainda superior ao resultado),
        podemos dividir por 60, obtendo como o valor de segundos.   
    --> Ainda, podemos dividir po 60 mais uma, obtendo a partir do seu resto o número de minutos, sendo o quociente desta 
        última divisão equivalente ao total de horas.
*/
void Jupiter_function(long int*sec_input, int *sec, int *min, long int *hour, long int *days){
    *days = (*sec_input / 35760); 
    *sec = (*sec_input % 35760) % 60;
    *min = ((*sec_input % 35760) / 60) % 60;
    *hour = ((*sec_input % 35760) / 60) / 60;
}

/*
    Função Mercury_function:
    --> Novamente, temos o calculo semelhante para minutos e segundos.
    --> Como cada dia possui o equivalente a 58 dias e 16 horas temos então : 1 dia em mercúrio equivale à 58*24 + 16,
        ou seja, 1408.
    Os calculos então seguem a mesma ideia das funções anteriores.
*/

void Mercury_function(long int*sec_input, int *sec, int *min, long int *hour, long int *days){
    *sec = *sec_input % 60;
    *min = (*sec_input / 60) % 60;
    *hour = (*sec_input / 3600) % 1408;
    *days = (*sec_input / (3600*1408));  
}
