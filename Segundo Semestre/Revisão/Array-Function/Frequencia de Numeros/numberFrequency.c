/*
	ICMC - INSTITUTO DE CIÊNCIAS MATEMÁTICAS E DE COMPUTAÇÃO
	BCC - Bacharelado em Ciências de Computação
	
	ICC II - Moacir Ponti
	Aluno: Bernardo Marques Costa
	Número: 11795551

	Programa para revisão de funções e vetores.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _num{
	int value;
	int frequency;
} NUM;

// Função analyseVector:
// analisa o vetor de inteiros dado como input, retornando um vetor de struct que contem,
// como um dicionário, os valores e suas frequências. 
NUM *analyseVector(int *v, int size, int *e_size){
	NUM *array = NULL;
	int counter = 0, pos_v = 0;
	int boolean = 1;

	while(pos_v < size){
		boolean = 1;
		// Analisando se o valor ja foi considerado e somando a frequencia.
		for(int i = 0; i < counter; i++){
			if (v[pos_v] == array[i].value){
				boolean = 0;
				array[i].frequency += 1;
			}
		}
		// Criando um novo indice da struct para o novo valor ainda não considerado.
		if (boolean){
			array = realloc(array, sizeof(NUM)*(counter+1));
			array[counter].value = v[pos_v];
			array[counter].frequency = 1;
			counter++;

		}
		pos_v++;
	}

	*e_size = counter;

	return array; 
}   
   
int main(int argc, char *argv[]){

	int *int_array = NULL;
	int counter = 0;

	while(!feof(stdin)){
		int_array = realloc(int_array, (counter+1)*sizeof(int));
		scanf("%d", &int_array[counter]);
		counter++;
	}

	NUM *analyses = NULL;
	int effective_size = 0;

	analyses = analyseVector(int_array, counter, &effective_size);
	
	for(int i = 0; i < effective_size; i++){
		printf("%d (%d)\n", analyses[i].value, analyses[i].frequency);
	}

	free(int_array);
	free(analyses);

	return 0;
}