// Bernardo Marques Costa - 11795551

#ifndef _UTILS_H_
#define _UTILS_H_

#define BUFFER_SIZE 128
#define TOKEN ';'

#include "boolean.h"

char *readline(FILE *);
char **read_csv(char *, int *);
char *part_string(char *, int , boolean *);

#endif