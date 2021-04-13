/*
    Aluno: Bernardo Marques Costa
    Número USP: 11795551
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <time.h>
#include <string.h>

#define EXTENTION ".dat"
#define DIRECTORY "./Data/"

#define BUFFER 128 

// Leitura de buffer
char *readline(FILE *stream){
    char character, *string = NULL;
    int pos = 0, multiplier = 1;
    do{
        if(pos % BUFFER == 0) string = realloc(string, (multiplier++)*(BUFFER));
        character = (int) fgetc(stream);
        
        if(character != '\r'){
            string[pos] = tolower(character);
            ++pos;
        }

    }while(character != '\n' && !feof(stream));
    
    string = realloc(string, pos);
    string[pos - 1] = '\0';

    return string;
}

// Realiza a leitura do arquivo .txt, que armazena a matriz de palavras
char **read_file(char *file_name, int *num_words){
    FILE *filepointer = NULL;

    if(!(filepointer = fopen(file_name, "r"))){
        printf("Error: failed to open file\n");
        return NULL;
    }
    
    // Contagem do número de linhas
    char aux_character;
    while(!feof(filepointer)){
        aux_character = fgetc(filepointer);
        if(aux_character == '\n')
            (*num_words)++;
    }

    char **txt_words = calloc(*num_words, sizeof(char*));
    
    fseek(filepointer, 0, SEEK_SET);
    
    // Leitura das palavras a partir do começo do arquivo
    for(int i = 0; i < *num_words; i++){
        txt_words[i] = readline(filepointer);
        
        if(txt_words[i][0] == '\0')
            free(txt_words[i]);
    }

    fclose(filepointer);

    return txt_words;
}


double getExecutionTime(time_t startTime, time_t endTime)
{
    double time_taken = (endTime-startTime)/(double)CLOCKS_PER_SEC; // in seconds
    #ifdef DEBUG
        printf("Tempo para executar tarefa: %.4lf\n", time_taken);
    #endif
    return time_taken;
}

// Salva os dado obtido em um arquivo para posterior análise
void saveTimeDataIntoFile(int functionDescriptor, char* data, double time, int executions){
	
    int pos = 0;
    while(data[pos] != 'k') pos++;
    pos++;
    char *dataSize = NULL;
    dataSize = calloc(pos, sizeof(char));
    
    for(int i = 0; i < pos; i++) dataSize[i] = data[i];

	char *filename = calloc(50, sizeof(char));
    
	// Bubblesort
	if(functionDescriptor == 1){
		char name[] = "bubblesort";
		for(int i = 0; i < strlen(name); i++)
			filename[i] = name[i];
	}
	// Insertion
	else if(functionDescriptor == 2){
		char name[] = "insertion";
		for(int i = 0; i < strlen(name); i++)
			filename[i] = name[i];
	}

    // Mergesort
    else if(functionDescriptor == 3){
        char name[] = "mergesort";
        for(int i = 0; i < strlen(name); i++)
			filename[i] = name[i];    
    }

	strcat(filename, EXTENTION);

	FILE *timeFilePointer = NULL;

	if(!(timeFilePointer = fopen(filename, "a+b"))){
		printf("Error opening %s file for writting\n", filename);
		free(filename);
        exit(EXIT_FAILURE);
	}

	fprintf(timeFilePointer, "%d,%f\n", atoi(dataSize), time);
	fclose(timeFilePointer);
	free(filename);
    free(dataSize);

	return;

}