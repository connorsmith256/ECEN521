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
	swap(pancakeStack,size-index)
}

void swap(int* pancakeStack, int size)
{
	int *end = &pancakeStack[size -1]]; 
	int swapTemp;
	
	for(int i=0; i<size/2; i++){
		swapTemp = pancakeStack[i];
		pancakeStack[i] = end[-i];
		end[-i] = swapTemp;
	}
}