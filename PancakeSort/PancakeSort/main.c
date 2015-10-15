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
	
	//Read File
	
	//Call Pancake Sort
	
	//Print Sort
	
    return 0;
}