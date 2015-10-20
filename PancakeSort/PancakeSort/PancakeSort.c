//
//  PancakeSort.c
//  PancakeSort
//
//  Created by Matthew James, Matthew Wyman, Connor Smith on 10/15/15.
//  Copyright © 2015 James Gang. All rights reserved.
//

#include "PancakeSort.h"
extern int verbose;

void Swap(int pancakeStack[], int index1, int index2) {
	int temp = pancakeStack[index1];
	pancakeStack[index1] = pancakeStack[index2];
	pancakeStack[index2] = temp;
}

void Flip(int pancakeStack[], int size, int endIndex) {
	printf("%d ", (size-endIndex));
	for (int i = 0, j = endIndex; i < j; i++, j--) {
		Swap(pancakeStack, i, j);
	}
}

int FindMaxIndex(int pancakeStack[], int size){ //Returns normal index
	int tempLargest = -1;
	int index = -1;
	for(int i = 0; i <= size; i++){
		if (pancakeStack[i] > tempLargest) {
			tempLargest = pancakeStack[i];
			index = i;
		}
	}
	return index;
}

void PancakeSort(int pancakeStack[], int size){
	PrintStack(pancakeStack, size);

	int num_flips = 0;
	int maxIndex; // NOT SORTED CURRENT MAX
	for(int i = size-1; i >= 0 ; i--){
		maxIndex = FindMaxIndex(pancakeStack, i);
		if (maxIndex != i) { //Not in right spot
			if (maxIndex != 0) {
				Flip(pancakeStack, size, maxIndex);
				num_flips++;
			}
			Flip(pancakeStack, size, i);
			num_flips++;
		}
	}
	printf("0 (%d)\n", num_flips);

	if (verbose)
		PrintStack(pancakeStack, size);
}

void PrintStack(int pancakeStack[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", pancakeStack[i]);
	}
	printf("\n");
}
