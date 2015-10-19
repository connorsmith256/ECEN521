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

#define MAX_SIZE 100
//Holds the pointer to our dynamically allocated array.
int inputArray[MAX_SIZE];

void ReadFile(FILE* f);
void ReadLine(char* line);

int main(int argc, const char* argv[]) {
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

void ReadFile(FILE* f) {
	const int LINE_SIZE = 4096;
	char line[LINE_SIZE];
	while (fgets(line, LINE_SIZE, f) != NULL) {
		ReadLine(line);
	}
}

void ReadLine(char* line) {
	int size = 1;

	while (1) {
		char* remaining = line;
		int nextNum = (int) strtol(line, &remaining, 10);
		if (line == remaining) { //Pointer didn't advance? end of string
			size--;
			break;
		}

		line = remaining;
		inputArray[size-1] = nextNum;
		size++;
	}

	//Call Pancake Sort
	PancakeSort(inputArray, size);
}
