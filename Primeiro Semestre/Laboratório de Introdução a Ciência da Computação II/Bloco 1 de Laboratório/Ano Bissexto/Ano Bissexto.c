#include <stdio.h>

int main (){
    int ano, resto;
    scanf ("%d", &ano);
    resto = ano % 4;
    if (resto == 0)
        printf ("SIM");
    else printf ("NAO");
    
    
    
    return 0;

}