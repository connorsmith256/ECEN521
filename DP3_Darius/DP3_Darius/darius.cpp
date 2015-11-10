#include "darius.h"

std::pair<std::vector<int>, int> darius() {
    std::pair<std::vector<int>, int> results;

    std::vector<int> cities;
    std::vector<int> newCities;
    std::vector<int> minCities;
    double cost = DBL_MAX;
    double newCost = DBL_MAX;
    double minCost = DBL_MAX;

    // create initial solution
    for (int i = 0; i < numCities; i++) {
        cities.push_back(i);
    }

    for (double temp = HIGH_TEMP; temp > LOW_TEMP && cost > COST_MIN; temp *= COOLING_FACTOR) {
        for (int i = 0; i < ITERATIONS_PER_TEMP; i++) {
            // create new solution based off current
            newCities = getNewCities(cities);
            // calculate cost for new solution
            newCost = getCost(cities, temp);

            // if better, or acceptably worse
            if (newCost < cost || exp(cost - newCost)/(K*temp) >= dRand()) {
                cities = newCities;
                cost = newCost;

                // remember best so far
                if (cost < minCost
                        && numIllegalCities(cities) == 0
                        && numMissingCities(cities) == 0) {
                    minCities = cities;
                    minCost = cost;
                }
            }
        }
    }

    // return best so far
    results.first = minCities;
    results.second = (int)(minCost/C1);
    return results;
}

double dRand() {
    double d = (double)rand() / RAND_MAX;
    return d;
}

std::vector<int> getNewCities(std::vector<int> cities) {
    std::vector<int> newCities;

    return cities;
}

int numIllegalCities(std::vector<int> cities){
    int count = 0;
    for (int i = 0; i < cities.size()-1; i++) {
        if (inputArray[cities.at(i)][cities.at(i+1)] == 0){
            count++;
        }
    }
    return count;
}

int calcSum(std::vector<int> cities) {
    int sum = 0;
    for (int i = 0; i < cities.size()-1; i++) {
        sum += inputArray[cities.at(i)][cities.at(i+1)];
    }
    return sum;
}

int numMissingCities(std::vector<int> cities){
    std::set<int> uniqueCities(cities.begin(), cities.end());
    return numCities-uniqueCities.size();
}

double getCost(std::vector<int> cities, double temp) {
    double cost1 = C1*calcSum(cities);
    double cost2 = (C2/temp)*numMissingCities(cities);
    double cost3 = (C3/temp)*numIllegalCities(cities);
    double cost = cost1 + cost2 + cost3;
    return cost;
}
