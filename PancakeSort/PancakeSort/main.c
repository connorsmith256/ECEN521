//
//  main.c
//  PancakeSort
//
//  Created by Matthew James, Matthew Wyman, Connor Smith on 10/15/15.
//  Copyright © 2015 James Gang. All rights reserved.
//

#include "PancakeSort.h"
#include <stdio.h>
#include <stdlib.h>

//Holds the pointer to our dynamically allocated array.
int *inputArray;
int initialSize = 10;

void ReadFile(FILE* f);
void ReadLine(char* line);
void ExpandArray(int *oldArray);

int main(int argc, const char * argv[]) {
	
	if (argc < 2)
	{
		printf("Error: no input file specified.\n");
		return 1;
	}
	
	FILE* f = fopen(argv[1], "r");
	if (f == NULL) {
		printf("Unable to open file!\n");
		return 1;
	}
	
	ReadFile(f);
	
	fclose(f);
	
    return 0;
}

void ReadFile(FILE* f)
{

	char line[4096];
	inputArray = NULL;
	while (fgets(line,4096,f) != NULL)
	{
		if (inputArray != NULL)
			free(inputArray);
		inputArray = NULL;
		
		initialSize = 10;
		inputArray = malloc(initialSize*sizeof(int));
		
		if (inputArray == NULL)
		{
			printf("Unable to allocate memory!\n");
			return;
		}
		
		ReadLine(line);
		
	}
}


void ReadLine(char* line)
{
	long int output;
	int index = 1;
	printf("%s\n",line);
	while(1)
	{
		char* nextNum = line;
		output = strtol(line, &nextNum, 10);
		if (line == nextNum)
		{
			//Pointer didn't advance? end of string
			index--;
			break;
		}
		else if (index > initialSize)
		{
			ExpandArray(inputArray);
		}
		
		line = nextNum;
		
		inputArray[index-1] = (int)output;
		index++;
	}
	//Call Pancake Sort
	PancakeSort(inputArray,index);
}

void ExpandArray(int* oldArray)
{
	int nextSize = initialSize*10;
	int *nextArray = malloc(nextSize*sizeof(int));
	for(int i = 0; i < initialSize; i++)
	{
		nextArray[i] = oldArray[i];
	}
	free(oldArray);
	initialSize = nextSize;
	inputArray = nextArray;
}