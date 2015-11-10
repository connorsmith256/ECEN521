#include "darius.h"

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
