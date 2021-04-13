#include <stdlib.h>
#include <stdio.h>

#include "search.h"

void printFormatedArray(int *netflixIdArray, int registerSize){
	printf("\n[ ");
	for(int i = 0; i < registerSize; ++i)
		printf("%d ", netflixIdArray[i]);
	printf("]\n");
}


int main(int argc, char *argv[]){
	
	int registerSize, numberSearchs;

	scanf("%d %d\n", &registerSize, &numberSearchs);

	int *netflixIdArray = NULL;
	netflixIdArray = (int*)calloc(registerSize, sizeof(int));

	for(int i = 0; i < registerSize; ++i)
		scanf("%d", &netflixIdArray[i]);

	int *key = (int *)calloc(numberSearchs, sizeof(int));
	int *searchAlgoritm = (int *)calloc(numberSearchs, sizeof(int));
	int *keyIndex = (int *)calloc(numberSearchs, sizeof(int));

	for(int i = 0; i < numberSearchs; ++i){
		scanf("%d %d", &searchAlgoritm[i], &key[i]);
	
		if(searchAlgoritm[i] == SEQUENTIAL) keyIndex[i] = sequentialSearch(netflixIdArray, key[i], registerSize);
		else if(searchAlgoritm[i] == BS_ITERATIVE) keyIndex[i] = binarySearchIterative(netflixIdArray, key[i], 0, registerSize - 1);
		else if(searchAlgoritm[i] == BS_RECURSIVE) keyIndex[i] = binarySearchRecursive(netflixIdArray, key[i], 0, registerSize - 1);
		
		if(keyIndex[i] != -1) keyIndex[i]++;

	}

	for(int i = 0; i < numberSearchs; ++i)
		printf("%d\n", keyIndex[i]);


	free(key);
	free(keyIndex);
	free(searchAlgoritm);
	free(netflixIdArray);

	return 0;
}
