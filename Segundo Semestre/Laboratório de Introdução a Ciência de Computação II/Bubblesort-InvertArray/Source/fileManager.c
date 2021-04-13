#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileManager.h"

#define FILENAME_PATTERN "numberlist"
#define EXTENTION ".dat"
#define DIRECTORY "./Data/"

// Function getFileName:
// Return the string that contains the path to the file where the input vector is stored.
char *getFileName(char *dataSize){
	char *fileName = NULL;
	
	int size = strlen(dataSize) + strlen(DIRECTORY);
	fileName = (char*)calloc(1, strlen(FILENAME_PATTERN) + size + strlen(EXTENTION) + 1);

	strcat(fileName, DIRECTORY);
	strcat(fileName, FILENAME_PATTERN);
	strcat(fileName, dataSize);
	strcat(fileName, EXTENTION);

	return fileName;
}

// Function readVectorDataFile: 
// Read the file where the input vector is stored and return the integer array. 
int *readVectorDataFile(char *dataSize){

	char *fileName = getFileName(dataSize);

	printf("%s\n", fileName);
	printf("%s\n", dataSize);
	FILE *filepointer = fopen(fileName, "rb");

	if(!filepointer){
		printf("Error opening the %s file\n", fileName);
		free(fileName);
		exit(EXIT_FAILURE);
	}

	int size = atoi(dataSize);
	
	int *vec = (int*)calloc(size, sizeof(int));

	for(int i = 0; i < size; i++)
		fread(&vec[i], sizeof(int), 1, filepointer);
	
	fclose(filepointer);
	
	return vec;

}

// Function saveTimeDataIntoFile:
// Use the data that was stored after the script and save the information about time and number of executions
// in an .dat file, separating in different filenames acording to wich function the program had analysed.
void saveTimeDataIntoFile(int functionDescriptor, char* dataSize, double time, int executions){
	
	char *filename = (char*)calloc(50, sizeof(char));
	
	// Bubblesort
	if(functionDescriptor == 1){
		char name[] = "bubblesort";
		for(int i = 0; i < strlen(name); i++)
			filename[i] = name[i];
	}
	// Invert
	else if(functionDescriptor == 2){
		char name[] = "invert";
		for(int i = 0; i < strlen(name); i++)
			filename[i] = name[i];
	}

	//strcat(filename, dataSize);
	strcat(filename, EXTENTION);

	FILE *timeFilePointer = NULL;

	if(!(timeFilePointer = fopen(filename, "a+b"))){
		printf("Error opening %s file for writting\n", filename);
		exit(EXIT_FAILURE);
	}

	fprintf(timeFilePointer, "%d,%f\n", atoi(dataSize), time);
	fclose(timeFilePointer);
	free(filename);

	return;

}