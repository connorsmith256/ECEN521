//
//  PancakeSort.h
//  PancakeSort
//
//  Created by Matthew James, Matthew Wyman, Connor Smith on 10/15/15.
//  Copyright © 2015 James Gang. All rights reserved.
//

#ifndef PancakeSort_h
#define PancakeSort_h

#include <stdio.h>

void Flip(int index, int* pancakeStack, int size);
void Swap(int* pancakeStack, int size);

int FindMaxIndex(int* pancakeStack, int size);

void PancakeSort(int* pancakeStack, int size);

#endif /* PancakeSort_h */
