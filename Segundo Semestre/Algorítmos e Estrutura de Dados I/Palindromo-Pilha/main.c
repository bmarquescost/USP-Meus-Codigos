/*
	ICMC - Instituto de Ciências Matemática e de Computação
	Algorítmo e Estrutura de Dados I
	
	Aluno: Bernardo Marque Costa (Número USP : 11795551)
	
	Utilização do TAD pilha
	Aplicação: palíndromos
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#include "stack.h"    // interface de usuário da pilha
#include "element.h"  // interface de usuário dos elementos

// Função readline: leitura (sem espaços) de uma string.
char *readline(FILE *stream){
	char *string = (char*)calloc(SIZE, sizeof(char));
	int pos = 0, multiplier = 1;
	boolean end_string = FALSE;
	do{
		if(pos % SIZE == 0) string = (char*) realloc(string, SIZE * (++multiplier));
		string[pos] = (int) fgetc(stream);
		
		string[pos] = tolower(string[pos]);
		
		if(string[pos] == '\n' || string[pos] == '\r' || feof(stream)) end_string = TRUE; 


		pos = isalnum(string[pos]) ? pos + 1 : pos;
	
	} while(!end_string);
	
	string[pos] = '\0';

	return string;
}	


int main(int argc, char *argv[]){
	char *input_string = NULL;
	input_string = readline(stdin);

	STACK* stack = create_stack();

	// Preenchendo a stack -> o último elemento da pilha é a última letra da string.
	for(int i = 0; i < strlen(input_string); i++){
		if(input_string[i] != ' '){
			ELEMENT *tmp = element_create((int) input_string[i]);
			stack_append(stack, tmp);
			element_delete(&tmp);
		}
	}

	int end = stack_size(stack);
	int match_found = 0;
	
	// Verificando se o topo da pilha é igual a primeira letra da palavra.
	// Análise estendida para até metade da pilha inicial.  
	for(int i = 0; i < end/2; i++){
		if(input_string[i] != ' ')
			if(input_string[i] == element_get_key(stack_top(stack))){
				match_found++;
				ELEMENT *tmp = stack_pop(stack);
				element_delete(&tmp);
			}	
	}	
	
	if(match_found == end/2) printf("É um palíndromo!\n");
	else printf("Não é um palíndromo!\n");

	free(input_string);
	stack_delete(&stack);

	return 0;
}