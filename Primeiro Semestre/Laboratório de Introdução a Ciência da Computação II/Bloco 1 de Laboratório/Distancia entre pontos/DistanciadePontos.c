#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX 100
int main (){
    int n;
    scanf ("%d", &n); 
    long double vetorx [MAX], vetory [MAX], soma = 0;
    int i;
    for (i = 0; i < n; i++)
    {
        scanf ("%Lf", &vetorx[i]);
        scanf ("%Lf", &vetory[i]);
    }
    for (int j = 0; j < n - 1; j++)
    {
        soma += sqrt(pow((vetorx[j]-vetorx[j+1]),2) + pow((vetory[j] - vetory [j+1]),2));
    }
    printf ("%0.4Lf\n", soma);
    return 0;
}