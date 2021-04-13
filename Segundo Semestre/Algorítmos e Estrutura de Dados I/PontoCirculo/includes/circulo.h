/*
	Bernardo Marques Costa - 11795551
	Arquivo include para a biblioteca circulo
	"Interface"
*/
#ifndef CIRCULO_H
#define CIRCULO_H

#include "ponto.h"

#define TRUE 1
#define FALSE 0

#define boolean int

typedef struct circulo_ CIRCULO;
 
CIRCULO *circulo_criar(PONTO *p, float raio); 
boolean circulo_set_ponto(CIRCULO *c, PONTO *p);
boolean circulo_set_raio(CIRCULO *c, int raio);
PONTO *circulo_get_ponto(CIRCULO *c);
int circulo_get_raio(CIRCULO *c);
void circulo_apagar(CIRCULO **circulo);

#endif