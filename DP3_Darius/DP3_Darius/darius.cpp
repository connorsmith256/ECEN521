//
//  main.c
//  Darius
//
//  Created by Matthew James, Matthew Wyman, and Connor Smith on 11/9/15.
//  Copyright © 2015 James Gang. All rights reserved.
//
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>
#include <limits.h>
#include <vector>

#define HIGH_TEMP 1000
#define LOW_TEMP 1
#define COOLING_FACTOR 0.9
#define COST_MIN 1
#define K 1
#define MAX_SIZE 25

//Holds the pointer to our dynamically allocated array.
int inputArray[MAX_SIZE][MAX_SIZE];
bool verbose;
int numCities;
int inputLine;

void ReadFile(FILE* f);
void ReadLine(char* line);
double dRand();
std::vector<char> getNewCities(std::vector<char> cities);
int getCost(std::vector<char> cities);
std::pair<std::vector<char>, int> darius();

double get_current_time() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double) tp.tv_sec + (double) tp.tv_usec * 1e-6);
}

int main(int argc, const char* argv[]) {
    verbose = false;
    if (argc < 2) {
        printf("Error: no input file specified.\n");
        return 1;
    }

    if (argc >= 3) {
        for(int i = 1; i < argc; i++) {
            printf("%s\n",argv[i]);
            if (strcmp(argv[i],"-v")) {
                printf("Verbose mode active!\n");
                verbose = true;
            }
        }
    }

    FILE* f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Unable to open file!\n");
        return 1;
    }

    inputLine = 0;
    for(int i = 0; i < MAX_SIZE; i++) {
        for(int k = 0; k < MAX_SIZE; k++) {
            inputArray[i][k] = 0;
        }
    }

    ReadFile(f);
    fclose(f);

    for(int i = 0; i < numCities; i++) {
        for(int k = 0; k < numCities; k++) {
            printf("%d ",inputArray[i][k]);
        }
        printf("\n");
    }

    double start = 0.0,end;
    if (verbose) {
        start = get_current_time();
    }
    darius();
    if (verbose) {
        end = get_current_time();
        printf("Time: %lf\n",end-start);
    }
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
    char input[256];
    int temp;

    if (inputLine == 0) {
        sscanf(line,"%d", &numCities);
    }
    else if (inputLine == 1) {
        sscanf(line,"%s",input);
    }
    else {
        for(int i = 0; i < inputLine - 1; i++) {
            if(i == inputLine - 2) {
                sscanf(&line[i+2],"%s", input);
            }
            else {
                sscanf(&line[i+2],"%s ", input);
            }
            temp = atoi(input);
            printf("%d\n",temp);
            inputArray[inputLine - 2][i-2] = temp;
            inputArray[i-2][inputLine-2] = temp;
        }
    }
    inputLine++;
}

std::pair<std::vector<char>, int> darius() {
    std::pair<std::vector<char>, int> results;

    std::vector<char> cities;
    std::vector<char> newCities;
    std::vector<char> minCities;
    int cost = INT_MAX;
    int newCost = INT_MAX;
    int minCost = INT_MAX;

    // create initial solution
    for (int i = 0; i < numCities; i++) {
        cities.push_back(i);
    }

    for (int temp = HIGH_TEMP; temp > LOW_TEMP && cost > COST_MIN; temp *= COOLING_FACTOR) {
        for (int i = 0; i < 100; i++) {
            // create new solution based off current
            newCities = getNewCities(cities);
            // calculate cost for new solution
            newCost = getCost(cities);

            // if better, or acceptably worse
            if (newCost < cost || exp(cost - newCost)/(K*temp) >= dRand()) {
                cities = newCities;
                cost = newCost;

                // remember best so far
                if (cost < minCost) {
                    minCities = cities;
                    minCost = cost;
                }
            }
        }
    }

    // return best so far
    results.first = minCities;
    results.second = minCost;
    return results;
}

double dRand() {
    double d = (double)rand() / RAND_MAX;
    return d;
}

std::vector<char> getNewCities(std::vector<char> cities) {
    std::vector<char> newCities;

    return newCities;
}

int getCost(std::vector<char> cities) {
    int cost = 0;

    return cost;
}
