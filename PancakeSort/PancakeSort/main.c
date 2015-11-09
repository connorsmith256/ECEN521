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
#include <string.h>
#include <sys/time.h>

#define MAX_SIZE 200
#define TRUE 1;
#define FALSE 0;

//Holds the pointer to our dynamically allocated array.
int inputArray[MAX_SIZE];
int verbose;

void ReadFile(FILE* f);
void ReadLine(char* line);

double get_current_time() {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return ((double) tp.tv_sec + (double) tp.tv_usec * 1e-6);
}

int main(int argc, const char* argv[]) {
	verbose = FALSE;
	if (argc < 2)
	{
		printf("Error: no input file specified.\n");
		return 1;
	}
	
	if (argc >= 3)
	{
		for(int i = 1; i < argc; i++)
		{
			printf("%s\n",argv[i]);
			if (strcmp(argv[i],"-v"))
			{
				printf("Verbose mode active!\n");
				verbose = TRUE;
			}
		}
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
	double start,end;
	if (verbose)
		start = get_current_time();
	PancakeSort(inputArray, size);
	if (verbose)
	{
		end = get_current_time();
		printf("Time: %lf\n",end-start);
	}
	
}
