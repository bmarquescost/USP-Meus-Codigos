// Bernardo Marques Costa - 11795551

#ifndef _UTILS_H_
#define _UTILS_H_

#define BUFFER_SIZE 128
#define TOKEN ';'

#include "boolean.h"

char *readline(FILE *stream);
char **read_csv(char *nome_csv, int *num_linhas);
char *part_string(char *linha_inteira, int start, boolean *is_end);

#endif