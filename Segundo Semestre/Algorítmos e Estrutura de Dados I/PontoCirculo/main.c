/*
	ICMC - Instituto de Ciências Matemáticas e de Computação
	BCC - Bacharelado em Ciências de Computação
	
	Algorítmos e Estrutura de Dados 1

	Programa: Tipo Abstrato de Dados -> Ponto e Circulo

	Professor: Rudinei Goulart
	Aluno: Bernardo Marques Costa
	Número USP: 11795551
*/

#include <stdlib.h>
#include <stdio.h>
#include "ponto.h"
#include "circulo.h"

// Função circulo_imprimir: imprime os elementos de um objeto círculo.
void circulo_imprimir(CIRCULO *c){
	PONTO *centro = circulo_get_ponto(c);
	if(c != NULL){
		printf("Circulo, coord. x: %.1f\n", ponto_get_x(centro));
		printf("Circulo, coord. y: %.1f\n", ponto_get_y(centro));
		printf("Raio: %d\n", circulo_get_raio(c));
	}
	else
		printf("Circulo inexistente\n");
}

int main(int argc, char *argv[]){
	float coordenada_x, coordenada_y;
	int raio;

	scanf("%f", &coordenada_x);
	scanf("%f", &coordenada_y);
	scanf("%d", &raio);

	// Criação de um ponto
	PONTO *ponto = ponto_criar(coordenada_x, coordenada_y);

	// Criação de um círculo
	CIRCULO *circulo = circulo_criar(ponto, (int) raio);

	ponto_print(ponto);
	circulo_imprimir(circulo);

	ponto_apagar(&ponto);
	circulo_apagar(&circulo);

	return 0;
}