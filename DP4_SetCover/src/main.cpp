#include <array>
#include <fstream>
#include <functional>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>
#include <sys/time.h>
#include <unordered_set>
#include <vector>

#define MAX_SIZE 1000

std::unordered_set<std::string> previousSolutions;
std::hash<char*> hash_func;
std::vector<std::array<int, MAX_SIZE> > sets;
std::array<int, MAX_SIZE> subsetIndexes;
std::array<int, MAX_SIZE> covered;

int maxNum;
int numSets;
int bestSoFar;

void printLabel(std::string label) {
	std::string dashes("-------------------------------");
	std::cout << dashes << "\n" << label <<	"\n" << dashes << "\n";
}

void printSet(std::array<int, MAX_SIZE> vec) {
	for (int i = 0; i < maxNum; i++) {
        if (vec.at(i)) {
			std::cout << i+1 << " ";
        }
	}
	std::cout << "\n";
}

void printBitVector(std::array<int, MAX_SIZE> vec) {
    for (int i = 0; i < maxNum; i++) {
        std::cout << vec.at(i) << " ";
    }
    std::cout << "\n";
}


void processHeader(const char* fileName) {
	std::pair<int, int> header;
	std::ifstream fstream(fileName);
	fstream >> maxNum >> numSets;
}

void getSets(const char* fileName) {
	sets.clear();
	std::ifstream fstream(fileName);
	std::string line;
	getline(fstream, line);
	getline(fstream, line);

	for (int i = 0; i < numSets; i++) {
		getline(fstream, line);

		std::istringstream ss(line);
		std::array<int, MAX_SIZE> newArray;
		newArray.fill(0);

		int num;
		while (ss >> num) {
			newArray.at(num-1) = 1;
		}
		sets.push_back(newArray);
	}
}

bool fullCover() {
	for (int i = 0; i < maxNum; i++) {
		if (!covered.at(i)) {
			return false;
		}
	}
	return true;
}

//Create a hash for the current solution, insert it into a table.
//Returns true if the solution has not yet been inserted, false
//otherwise.
bool isNew(std::array<int, MAX_SIZE> solution) {
	char vecToString[MAX_SIZE];
	for (int i = 0; i < numSets; i++) {
        vecToString[i] = solution.at(i) + '0';
	}
	std::string newSolution(vecToString);

	bool exists = previousSolutions.count(newSolution) > 0;
	if (exists) {
		return false;
	}

	previousSolutions.insert(newSolution);
	return true;
}

//Applies the selected subset to the covering set.
inline void applySubset(int index, std::array<int, MAX_SIZE> &covered){
    for(int i = 0; i < maxNum; i++)
    {
        covered.at(i) += sets.at(index).at(i);
    }
}

//Unapplies the selected subset from the covering set.
inline void unapplySubset(int index, std::array<int, MAX_SIZE> &covered){
    for(int i = 0; i < maxNum; i++)
    {
        covered.at(i) -= sets.at(index).at(i);;
    }
}

//Finds the minimum set cover for a universe.
void getMinimumSetCoverIndexes(int index, int depth) {

    // std::cout << "depth: " << depth << "\n";
    // printSet(subsetIndexes);
    // printBitVector(covered);

    //Don't try to find solutions worse than the best so far
    if (depth >= bestSoFar) {
    	return;
    }

    //Do not continue if we've already looked at this solution.
    if (index > 0 && !isNew(subsetIndexes)) {
    	// std::cout << "Not new. Returning.\n";
    	return;
    }

    //If we've already included this index in our set, go to the next one.
    while(covered.at(index) != 0) {
        index++;
    }

    //Once we reach the end of the list.
    if (index == maxNum) {
        //If this is the best cover so far, print it.
        if (fullCover()) {
            bestSoFar = depth;
            std::cout << "(" << depth << ") ";
            for (int i = 0; i < maxNum; i++) {
                if (subsetIndexes.at(i)) {
                    std::cout << i+1 << " ";
                }
            }
            std::cout << "\n";
        }
        return;
    }

    // std::cout << "Looking for a set containing: " << index+1 << std::endl;
    for (int i = 0; i < numSets; i++){
		if (!subsetIndexes.at(i) && sets.at(i).at(index)) {
            // printSet(sets.at(i));
			subsetIndexes.at(i) = 1;
            applySubset(i, covered);
			getMinimumSetCoverIndexes(index+1, depth+1);
            unapplySubset(i, covered);
			subsetIndexes.at(i) = 0;
		}
	}
}

double get_current_time() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double) tp.tv_sec + (double) tp.tv_usec * 1e-6);
}

//Entry Point
int main(int argc, char* argv[]) {
	std::string fileName(argv[1]);
	processHeader(fileName.c_str());

	printLabel("Max number, number of sets:");
	std::cout << maxNum << "\n" << numSets << "\n";

	getSets(fileName.c_str());
	printLabel("Input sets:");
	for (std::vector<std::array<int, MAX_SIZE> >::iterator I = sets.begin(),
			IE = sets.end(); I != IE; I++) {
		std::cout << "(" << (I - sets.begin() + 1) << ") ";
		printSet(*I);
	}

	printLabel("Results:");

	double start_time = get_current_time();

	previousSolutions.clear();
	subsetIndexes.fill(0);
	covered.fill(0);
	bestSoFar = MAX_SIZE;
	getMinimumSetCoverIndexes(0, 0);

	double end_time = get_current_time();
	std::cout << "Execution time (s): " << (end_time - start_time) << "\n";

	return 0;
}
