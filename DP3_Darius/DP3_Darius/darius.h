#ifndef __DARIUS_H
#define __DARIUS_H

#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <vector>
#include <set>

#define MAX_SIZE 25

// annealing constants
#define HIGH_TEMP 1000
#define LOW_TEMP 1
#define COOLING_FACTOR 0.9
#define COST_MIN 1
#define K 1

// cost function constants
#define C1 1
#define C2 1
#define C3 1

extern int numCities;
extern int inputArray[MAX_SIZE][MAX_SIZE];

double dRand();
std::vector<int> getNewCities(std::vector<int>);
int getCost(std::vector<int>, int);
std::pair<std::vector<int>, int> darius();

#endif