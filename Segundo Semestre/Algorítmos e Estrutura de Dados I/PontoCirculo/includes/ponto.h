/*
	Bernardo Marques Costa - 11795551
	Arquivo de include da bilbioteca ponto
	"Interface"
*/
#ifndef PONTO_H
#define PONTO_H

#define TRUE 1
#define FALSE 0
#define boolean int

typedef struct ponto_ PONTO;

PONTO *ponto_criar(float x, float y);
void ponto_apagar(PONTO **p);
boolean ponto_set(PONTO *p, float x, float y);
float ponto_get_x(PONTO *p);
float ponto_get_y(PONTO *p);
void ponto_print(PONTO *p);

#endif