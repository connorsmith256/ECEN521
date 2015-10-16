//
//  PancakeSort.c
//  PancakeSort
//
//  Created by Matthew James, Matthew Wyman, Connor Smith on 10/15/15.
//  Copyright © 2015 James Gang. All rights reserved.
//

#include "PancakeSort.h"

void Flip(int index, int* pancakeStack, int size)
{
	//int* pancakeStack point to top of Pancakes (Left)
	Swap(pancakeStack,(size-index+1)) //We want to include the index hence the +1
	
}

void Swap(int* pancakeStack, int size)
{
	int *end = &pancakeStack[size -1]]; 
	int swapTemp;
	printf("%d ",size); //Prints the flip target
	for(int i=0; i<size/2; i++){
		swapTemp = pancakeStack[i];
		pancakeStack[i] = end[-i];
		end[-i] = swapTemp;
	}
}

int FindMaxIndex(int* pancakeStack, int size){ //Returns normal index
	int = tempLargest = 0;
	int = index = -1;
	for(int i=0; i<size; i++){
		if(pancakeStack[i]>tempLargest)
			tempLargest = pancakeStack[i];
			index = i;
	}
	return index;
}

void PancakeSort(int* pancakeStack, int size){
	int currentSize = size;
	int currentMaxIndex; // NOT SORTED CURRENT MAX
	for(int i = 0; i < currentSize ; i++){
		currentMaxIndex = FindMaxIndex(pancakeStack, currentSize); // 
		if(currentMaxIndex != i){ //Not in right spot
			Flip(currentMaxIndex, pancakeStack, currentSize);
			Flip(currentSize,pancakeStack,currentSize);
		}
		currentSize--;
		i=0;
	}
}