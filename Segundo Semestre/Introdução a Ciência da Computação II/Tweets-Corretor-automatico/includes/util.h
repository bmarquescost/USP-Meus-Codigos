#ifndef _UTIL_H_
#define _UTIL_H_

#include <stdio.h>

#define BUFFER 1024

char *readline(FILE *);
char **parse_line(char *, int *);
void clear_line(char *);
char *create_filepath(char *, char *);
int num_of_lines(FILE *);


#endif