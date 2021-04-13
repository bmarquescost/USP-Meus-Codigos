#include "search.h"
#include <stdio.h>
#include <stdlib.h>

int sequentialSearch(int *array, int key, int size){
	for(int i = 0; i < size; ++i)
		if(key == array[i]) return i;
	return -1;
}

int binarySearchIterative(int *array, int key, int start, int end){
	
	int middle;

	while(start <= end){

		middle = start + (end - start) / 2;

		if(array[middle] == key) return middle;

		else if(array[middle] > key){
		 	end = middle - 1; 
		} 
		else if(array[middle] < key){
			start = middle + 1;
		}
	}
	return -1;
}


int binarySearchRecursive(int *array, int key, int start, int end){

	if(start <= end){

		int middle = start + (end - start) / 2;

		if(array[middle] == key) return middle;
		
		else if(array[middle] > key) return binarySearchRecursive(array, key, start, middle - 1);
		
		else if(array[middle] < key) return binarySearchRecursive(array, key, middle + 1, end);
	}
	
	return -1;
}	
