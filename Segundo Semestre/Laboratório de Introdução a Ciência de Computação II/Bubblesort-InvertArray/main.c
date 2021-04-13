#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "function.h"
#include "fileManager.h"
#include "StopWatch.h"

int main(int argc,char *argv[]){
	
	if(argc < 4){
		printf("Usage: %s < function > < N executions > < Number of data >\n", argv[0]);
		printf("\t- function available: bubblesort invert\n\t- N executions: integer\n\t- Number of data: 10, 100, 1000, 5000, 10000, 100000, 1000000\n");
		exit(EXIT_FAILURE);
	}
		
	clock_t startTime, endTime;
	double averageTime = 0;


	int dataSize = atoi(argv[3]);
	int nExecutions = atoi(argv[2]);

	int *dataVector = NULL;
	dataVector = readVectorDataFile(argv[3]);

	if(strcmp(argv[1], "bubblesort") == 0){
		
		for(int i = 0; i < nExecutions; i++){

			startTime = clock();
			bubblesort(dataVector, dataSize);
			endTime = clock();

			averageTime += getExecutionTime(startTime, endTime);
		}

		averageTime = averageTime /(double) nExecutions;

        saveTimeDataIntoFile(1, argv[3], averageTime, nExecutions);
        		
	}

	else if (strcmp(argv[1], "invert") == 0){
		for(int i = 0; i < nExecutions; i++){
			startTime = clock();
			invertVector(dataVector, dataSize);
			endTime = clock();
			averageTime += getExecutionTime(startTime, endTime);
		}
		averageTime = averageTime /(double) nExecutions;
        saveTimeDataIntoFile(2, argv[3], averageTime, nExecutions);
	}

	free(dataVector);

	return 0;
}