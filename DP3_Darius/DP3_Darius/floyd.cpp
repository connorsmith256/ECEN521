#include "floyd.h"

int dist[MAX_SIZE][MAX_SIZE];
int next[MAX_SIZE][MAX_SIZE];

void floyd(int dim, int matrix[MAX_SIZE][MAX_SIZE]) {
	// initialize
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			int val = matrix[i][j];
			matrix[i][j] = (val >= 0) ? val : INT_MAX;
			next[i][j] = j;
		}
	}

	// compute
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			for (int k = 0; k < dim; k++) {
				int temp = matrix[i][k] + matrix[k][j];
				if (temp >= 0 && temp < matrix[i][j]) {
					matrix[i][j] = temp;
					next[i][j] = next[i][k];
				}
			}
		}
	}
}

std::vector<int> getPath(int city1, int city2) {
	std::vector<int> path;

	if (next[city1][city2] == SENTINEL) {
		return path;
	}
	path.push_back(city1);
	while (city1 != city2) {
		city1 = next[city1][city2];
		path.push_back(city1);
	}

	return path;
}
