/*
	Bernardo Marques Costa - 11795551
	Arquivo source para a biblioteca ponto
*/
#include <stdlib.h>
#include <stdio.h>

#include "ponto.h"

struct ponto_ {
	float x;	// Coordenada x do ponto
	float y;	// Coordenada y do ponto
};


// Função ponto_criar: retorna uma instancia do tipo ponto.
PONTO *ponto_criar(float x, float y){
	PONTO *ponto = NULL;
	ponto = (PONTO *)calloc(1, sizeof(PONTO));

	if(ponto != NULL){
		ponto->x = x;
		ponto->y = y;
	}

	return ponto;
}

// Função ponto_apagar: responsável por destruir uma instancia do tipo ponto
void ponto_apagar(PONTO **p){
	if((*p) != NULL){
		free(*p);
		*p = NULL;
	}
}

// Função ponto_set: altera os valores das coordenadas de um objeto do tipo ponto
boolean ponto_set(PONTO *p, float x, float y){
	if(p != NULL){
		p->x = x;
		p->y = y;
	
		return TRUE;
	}

	return FALSE;
}

// Função ponto_get_x: retorna o valor da coordenada x de um objeto ponto.
float ponto_get_x(PONTO *p){
	if(p != NULL){
		return p->x;
	}
	else{
		printf("\nERRO: ponto_get_x\nAcessando estutura nula.\n");
		exit(1);
	}
}


// Função ponto_get_y: retorna o valor da coordenada y de um objeto ponto.
float ponto_get_y(PONTO *p){
	if(p != NULL){
		return p->y;
	}
	else{
		printf("\nERRO: ponto_get_y\nAcessando estutura nula.\n");
		exit(1);
	}
}


// Função ponto_print: imprime os valores das coordenadas do objeto ponto.
void ponto_print(PONTO *p){
	if(p != NULL){
		printf("Ponto, coord. x: %.1f\n", p->x);
		printf("Ponto, coord. y: %.1f\n", p->y);
	}
	else printf("Ponto inexistente\n");
}