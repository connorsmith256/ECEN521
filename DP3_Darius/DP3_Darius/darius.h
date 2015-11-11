#ifndef __DARIUS_H
#define __DARIUS_H

#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <float.h>
#include <vector>
#include <set>
#include <algorithm>

#include "constants.h"
#include "floyd.h"

// annealing constants
#define HIGH_TEMP 1000
#define LOW_TEMP 1
#define COOLING_FACTOR 0.9
#define ITERATIONS_PER_TEMP 1000
#define COST_MIN 1
#define K 1

// cost function constants
#define C1 1
#define C2 100
#define C3 100

extern int numCities;
extern int inputArray[MAX_SIZE][MAX_SIZE];

std::pair<std::vector<int>, int> darius();
double dRand();
std::vector<int> getNewCities(std::vector<int>);
std::vector<int> insertCity(std::vector<int>);
std::vector<int> removeCity(std::vector<int>);
std::vector<int> swapCities(std::vector<int>);

int numIllegalCities(std::vector<int> cities);
int calcSum(std::vector<int> cities);
int numMissingCities(std::vector<int> cities);
double getCost(std::vector<int>, double);
void print(std::vector<int> cities);

#endif