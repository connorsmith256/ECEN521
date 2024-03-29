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
    cities.push_back(0);
    for (int i = 1; i < numCities; i++) {
        cities.push_back(i);
    }

    for (double temp = HIGH_TEMP; temp > LOW_TEMP && cost > COST_MIN; temp *= COOLING_FACTOR) {
        for (int i = 0; i < ITERATIONS_PER_TEMP; i++) {
            // create new solution based off current
            newCities = getNewCities(cities);
            // calculate cost for new solution
            newCost = getCost(newCities, temp);

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
    results.second = (int)(minCost/C1);
    return results;
}

double dRand() {
    double d = (double)rand() / RAND_MAX;
    return d;
}

std::vector<int> getNewCities(std::vector<int> cities) {
    long size = cities.size();
    int method = 2;
    switch(method) {
		case 0:                                                 // add one
			return insertCity(cities);
		case 1:                                                 // remove one
			return removeCity(cities);
		case 2:                                                 // swap two
			return swapCities(cities);
		default:
			return cities;
    }
}

std::vector<int> insertCity(std::vector<int> cities)
{
	int newCity, position1;
	long size = cities.size();
	std::vector<int> newCities(cities); //Create a copy of the city list.
	newCity = rand() % numCities;
	position1 = (size > 0) ? (rand() % size) : 0;
	newCities.insert(newCities.begin()+position1, newCity);
	return newCities;
}

std::vector<int> removeCity(std::vector<int> cities)
{
	int position1;
	long size = cities.size();
	std::vector<int> newCities(cities); //Create a copy of the city list.
	position1 = rand() % size;
	newCities.erase(newCities.begin()+position1);
	return newCities;
}

std::vector<int> swapCities(std::vector<int> cities)
{
	std::vector<int> newCities(cities); //Create a copy of the city list.
    int position1, position2;

    long size = cities.size();
    position1 = rand() % (size-1) + 1;
	do {
		position2 = rand() % (size-1) + 1;
	} while (position1 == position2);

	std::iter_swap(newCities.begin()+position1, newCities.begin()+position2);

    return newCities;
}

int numIllegalCities(std::vector<int> cities){
    int size = (int)cities.size();
    int count = 0;
    for (int i = 0; i < size-1; i++) {
        if (inputArray[cities.at(i)][cities.at(i+1)] == SENTINEL){
            count++;
        }
    }
    return count;
}

int calcSum(std::vector<int> cities) {
    int size = (int)cities.size();
    int sum = 0;
    for (int i = 0; i < size-1; i++) {
        int temp = inputArray[cities.at(i)][cities.at(i+1)];
        sum += (temp >= 0) ? temp : 0;
    }
    return sum;
}

int numMissingCities(std::vector<int> cities){
    std::set<int> uniqueCities(cities.begin(), cities.end());
    return numCities-uniqueCities.size();
}

double getCost(std::vector<int> cities, double temp) {
    double cost = calcSum(cities);
    return cost;
}

void print(std::vector<int> cities) {
    int size = (int)cities.size();
    for (int i = 0; i < size; i++) {
        printf("%d ", cities.at(i));
    }
}
