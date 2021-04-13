#ifndef _SEARCH_H_
#define _SEARCH_H_

enum searchAlgoritm{
	SEQUENTIAL = 1,
	BS_ITERATIVE = 2,
	BS_RECURSIVE = 3,
};


int sequentialSearch(int *array, int key, int size);
int binarySearchIterative(int *array, int key, int start, int end);
int binarySearchRecursive(int *array, int key, int left, int right);


#endif