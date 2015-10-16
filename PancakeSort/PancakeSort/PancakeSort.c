//
//  PancakeSort.c
//  PancakeSort
//
//  Created by Matthew James, Matthew Wyman, Connor Smith on 10/15/15.
//  Copyright © 2015 James Gang. All rights reserved.
//

#include "PancakeSort.h"

int flips = 0;
int originalSize = 0;
void Flip(int index, int* pancakeStack, int size)
{
	//int* pancakeStack point to top of Pancakes (Left)
	Swap(pancakeStack,(size-index),size); //We want to include the index hence the +1
	flips++;
}

void Swap(int* pancakeStack, int index, int size)
{
	int *end = &pancakeStack[index -1];
	int swapTemp;
	printf("%d ",(originalSize-size)+index); //Prints the flip target
	for(int i=0; i<index/2; i++){
		swapTemp = pancakeStack[i];
		pancakeStack[i] = end[-i];
		end[-i] = swapTemp;
	}
}

int FindMaxIndex(int* pancakeStack, int size){ //Returns normal index
	int tempLargest = 0;
	int index = -1;
	for(int i=0; i<size; i++){
		if(pancakeStack[i]>tempLargest)
		{
			tempLargest = pancakeStack[i];
			index = i;
		}
	}
	//printf("Max Index: %d\n",index);
	return index;
}

void PancakeSort(int* pancakeStack, int size){
	int currentSize = size;
	originalSize = size;
	int currentMaxIndex; // NOT SORTED CURRENT MAX
	for(int i = 0; i < currentSize ; i++){
		currentMaxIndex = FindMaxIndex(pancakeStack, currentSize); // 
		if(currentMaxIndex != i){ //Not in right spot
			Flip(currentMaxIndex, pancakeStack, currentSize);
			Flip((currentSize-1),pancakeStack,currentSize);
		}
		currentSize--;
		i=0;
	}
	printf("(%d)\n",flips);
}