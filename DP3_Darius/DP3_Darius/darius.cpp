#include "darius.h"

std::pair<std::vector<int>, int> darius() {
    std::pair<std::vector<int>, int> results;

    std::vector<int> cities;
    std::vector<int> newCities;
    std::vector<int> minCities;
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
            newCost = getCost(cities, temp);

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

int getCost(std::vector<int> cities, int temp) {
    int cost1 = C1*calcSum(cities);
    int cost2 = (C2/temp)*numMissingCities(cities);
    int cost3 = (C3/temp)*numIllegalCities(cities);
    int cost = cost1 + cost2 + cost3;
    return cost;
}
