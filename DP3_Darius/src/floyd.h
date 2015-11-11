#ifndef __FLOYD_H
#define __FLOYD_H

#include <vector>

#include "constants.h"

void floyd(int dim, int matrix[MAX_SIZE][MAX_SIZE]);
std::vector<int> getPath(int city1, int city2);

#endif