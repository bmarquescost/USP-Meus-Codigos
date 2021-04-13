#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main (){
    int a,b,c, hipotenusa, cateto1,cateto2;
    scanf("%d",&a);
    scanf("%d",&b);
    scanf("%d",&c);

    if (a > b && a > c) 
    {
        cateto1 = b;
        cateto2 = c;
        hipotenusa = a;
    }
    else if (b > a && b >c)
    {
        cateto1 = a;
        cateto2 = c;
        hipotenusa = b;
    }   
    else if (c > a && c > b)
    {
        cateto1 = a;
        cateto2 = b;
        hipotenusa = c;

    } 
    if (pow(hipotenusa,2) == pow (cateto1,2) + pow(cateto2,2)) printf ("SIM");
    else printf ("NAO");
    

    return 0;
}