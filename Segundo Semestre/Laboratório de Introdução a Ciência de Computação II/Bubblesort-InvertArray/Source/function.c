#include <stdio.h>
#include <stdlib.h>
#include "function.h"

void bubblesort(int *vec, int size){
	
	for(int i = 0; i < size; i++){   // primeira vez -> a + c
									 // apos a primeira -> n(2a + c)

		for(int j = 0; j < size - 1; j++){ // primeira vez    -> n(a + c) = an + cn
										   // apos a primeira -> n(n - 1)(2a + c))  = (n² - n)(2a + c) = 2an² + cn² - 2an - cn
			if(vec[j] > vec[j+1]){         // n(n - 1)(2p + a + c)  = (n²  - n)(2p + a + c) = 2pn² + an² + cn² -2pn - an - cn
				//swap
				int temp =  vec[j];        // n(n - 1)(p + a)   = (n² - n)(p + a)   = pn² + an² -pn - an
				vec[j] = vec[j + 1];       // n(n - 1)(2p + 2a) = (n² - n)(2p + 2a) = 2pn² + 2an² -2pn - 2an
				vec[j + 1] = temp;         // n(n - 1)(p + 2a)  = (n² - n)(p + 2a)  = pn² + 2an² - pn - 2an 
			}	
		}
		// f(n) = a + c + 2an + cn + an + cn + 2an² + cn² - 2an - cn + 2pn² + an² + cn² - 2pn -an -cn + pn² + an² -pn - an +
	}	// '-> + 2pn² + 2an² -2pn - 2an + pn² + 2an² - pn - 2an
}		
		// considerando a = c = p = C
   		// f(n) = 16Cn² - 11Cn + 2C



void invertVector(int *vec, int size){
	
	for(int i = 0; i < size/2; i++){  // primeira vez -> a + c
									  // apos a primeira -> n/2(2a + c)
		
		int temp = vec[i];              // n/2(p + a)         
		vec[i] = vec[size - i - 1];     // n/2(2a + 2p)
		vec[size - i -1] = temp;       	// n/2(2a + p)
	}
}      // f(n) = a + c + 2an/2 + cn/2 + pn/2 + an/2 + 2an/2 + 2pn/2 + 2an/2 + pn/2  
       // f(n) = 7an/2 + 4pn/2 + cn/2 + a + c
	   // considerando a = c = p = C
	   // f(n) = 12Cn/2 + 2C => f(n) = 6Cn + 2C





