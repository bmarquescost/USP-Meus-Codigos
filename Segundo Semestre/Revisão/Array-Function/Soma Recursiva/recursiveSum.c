#include <stdio.h>
#include <stdlib.h>

int soma_recursivamente(int *v, int soma){
	
	if (*v == -1){
		printf("Retornando a soma\n");
		return soma;
	}
	else{
		soma += *v;
		return soma_recursivamente(v+1, soma);
	}
}

int main(int argc, char *argv[]){
		
	int soma = 0;
	int v[] = {1,2,3,4,5,6,7,8,9,10,-1};

	soma = soma_recursivamente(v, 0);
	printf("Soma: %d\n",soma);

	return 0;
}