/*
    Aluno : Bernardo Marques Costa
    Número USP : 11795551   
    Programa: BANCO DE DADOS
*/
#ifndef _SUPORT_SGBD_
#define _SUPORT_SGBD_


#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define TOKEN ':'           // Definindo o token de separação presente no arquivo de metadados que será lido pelo programa.
#define SEPARATOR ','       // Definindo o elemento separador das informações em cada comando de inserção. 
#define STRING_PATTERN '"'  // Definindo o elemtento indicador de string.

// enumeração arbitrária referenciando cada um dos comandos.
enum instructions{
    INSERT_MODE = 0,
    INDEX_MODE = 1,
    SEARCH_MODE = 2,
    EXIT = 3,
};

// struct de inserções
typedef struct _insertion{
    char **inserted;                // vetor de strings, em que cada linha corresponde à string de reposta a um campo.
    unsigned int key;               // chave da inserção (por padrão sempre inteira positiva).
    unsigned int offset_insertion;  // offset da inserção no arquivo de extensão .reg.
} INSERTION;

// struct de search (dados presentes no arquivo .idx, ordenado de acordo com a chave).
typedef struct _search{
    unsigned int key;       // chave da inserção.
    unsigned int offset;    // offset da inserção.
} SEARCH_DATA;

// struct dos campos.
typedef struct _fields{
    char *field_name;           // armazena o nome ou descrição do campo.
    char *field_type;           // armazena o tipo deste campo (int, float, double, char[<numero>]).
    unsigned int bytes_size;    // armazena, de acordo com o tipo do campo, quantos bytes este tipo de variável ocupará.
} FIELD;

// struct dos dados do arquivo.
typedef struct _archives_data{  
    char *data_file_name;           // armazena o nome do arquivo .dat em que será lido os metadados.
    char *register_file_name;       // armazena o nome do arquivo .reg, em que será inserido todos dados do comando inset.
    char *idx_file_name;            // string do nome do arquivo .idx, em que será inserido de maneira ordenada apenas a chave e o offset das inserções. 
    char *key_name;                 // armazena o nome ou descrição da chave.
    char *key_type;                 // armazena o tipo da chave (por padrão inteiro positivo).
    unsigned int number_of_fields;  // armazena o número de campos, contabilizado no arquivo .dat
    unsigned int insertion_counter; // armazena o número de inserções feitas pelo usuário.
    unsigned int offset;            // armazena o offset padrão dado o arquivo de metadados.
} ARCHIVES_DATA;


char *readline(FILE *);
ARCHIVES_DATA *initializeArchiveInfo();
FIELD *readMetadata(ARCHIVES_DATA *);
char *createIdxName(char *);
void separateByToken(ARCHIVES_DATA *, FIELD *);
void findType(ARCHIVES_DATA *, FIELD *);
int decodeInstruction(char *);
void standarOffset(ARCHIVES_DATA *, FIELD *);
void insertFunction(ARCHIVES_DATA *, FIELD *, INSERTION **, char *);
void createIdxFile(ARCHIVES_DATA *, INSERTION *);
void searchFunction(ARCHIVES_DATA *, FIELD *, INSERTION *, char *);
void createFileRegister(ARCHIVES_DATA *, FIELD *, INSERTION *);
void freeDataSruct(ARCHIVES_DATA **);
void freeInsertions(INSERTION **, unsigned int , unsigned int );
void freeFields(FIELD **, unsigned int );
void freeMatrix(char ***, unsigned int );

#endif