/*
	Bernardo Marques Costa - 11795551
	Arquivo source para a biblioteca circulo
*/
#include <stdio.h>
#include <stdlib.h>

#include "circulo.h"

struct circulo_ {
	PONTO *centro;  // Objeto do tipo ponto para representar o centro de um objeto do tipo circulo.
	int raio;		// Raio do círculo.
};

// Função circulo_criar: retorna uma instancia do tipo circulo, recebendo como parâmetros o ponto central e o raio.
CIRCULO *circulo_criar(PONTO *p, float raio){
	CIRCULO *circulo = NULL;

	if(p != NULL && raio > 0){
		circulo = (CIRCULO *)calloc(1, sizeof(CIRCULO));
		circulo->centro = ponto_criar(ponto_get_x(p), ponto_get_y(p));
		circulo->raio = raio;
	}

	return circulo;
}

// Função circulo_set_ponto: responsável por alterar coordenadas do ponto central do circulo.
boolean circulo_set_ponto(CIRCULO *c, PONTO *p){
	if(c != NULL && p != NULL){
		boolean resultado = ponto_set(c->centro, ponto_get_x(p), ponto_get_y(p));
		return resultado;
	}	
	return FALSE;
}

// Função ciruclo_set_raio: responsável por alterar o valor do raio de um circulo.
boolean circulo_set_raio(CIRCULO *c, int raio){
	if(c != NULL && raio > 0){
		c->raio = raio;
		return TRUE;
	}
	printf("Erro ao alterar raio:\nCirculo inexistente ou raio menor que 0.\n");
	return FALSE;
}

// Função circulo_get_ponto: retorna o objeto correspondente ao ponto central.
PONTO *circulo_get_ponto(CIRCULO *c){
	if(c != NULL){
		return c->centro;
	}
	else{
		printf("Circulo inexistente\n");
		return NULL;		
	} 
}

// Função circulo_get_raio: retorna o valor do raio de um objeto do tipo círculo.
int circulo_get_raio(CIRCULO *c){
	if(c != NULL){
		return c->raio;
	}
	else{
		printf("Acessando raio de circulo inexistente\n");
		exit(1);
	}
}

// Função circulo_apagar: apaga um objeto do tipo circulo.
void circulo_apagar(CIRCULO **circulo){
	if((*circulo) != NULL){
		free((*circulo)->centro);
		(*circulo)->centro = NULL;
		free(*circulo);
		(*circulo) = NULL;
	}
}

