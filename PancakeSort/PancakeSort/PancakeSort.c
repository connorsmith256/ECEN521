//
//  PancakeSort.c
//  PancakeSort
//
//  Created by Matthew James, Matthew Wyman, Connor Smith on 10/15/15.
//  Copyright © 2015 James Gang. All rights reserved.
//

#include "PancakeSort.h"

void Flip_i(int index, int* pancakeStack, int size)
{
	//int* pancakeStack point to top of Pancakes (Left)
	Swap(pancakeStack,(size-index+1)) //We want to include the index hence the +1
}

void Swap(int* pancakeStack, int size)
{
	int *end = &pancakeStack[size -1]]; 
	int swapTemp;
	
	for(int i=0; i<size/2; i++){
		swapTemp = pancakeStack[i];
		pancakeStack[i] = end[-i];
		end[-i] = swapTemp;
	}
}
//PancakeIndex(TM) is a patented form of indexing that indexes from the bottom of a Pancake Stack to the top.
FindMax(int* pancakeStack, int size){ //Returns the PancakeIndex(TM) of the largest value
	int = tempLargest = 0;
	int = index = -1;
	for(int i=0; i<size; i++){
		if(pancakeStack[i]>tempLargest)
			tempLargest = pancakeStack[i];
			index = i;
	}
	return (size - index);
}