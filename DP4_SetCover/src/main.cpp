#include <array>
#include <fstream>
#include <functional>
#include <iostream>
#include <set>
#include <stdio.h>
#include <string>
#include <sstream>
#include <sys/time.h>
#include <vector>

#define MAX_SIZE 1000

std::set<int> previousSolutions;
std::hash<std::string> hash_func;
std::vector<std::array<int, MAX_SIZE> > sets;
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

bool fullCover(std::array<int, MAX_SIZE> subsetIndexes) {
	std::array<int, MAX_SIZE> universalSet;
	universalSet.fill(0);

	for (int i = 0; i < MAX_SIZE; i++) {
		if (subsetIndexes.at(i)) {
			for (int j = 0; j < maxNum; j++) {
				if (sets.at(i).at(j)) {
					// std::cout << j << " ";
					universalSet.at(j) = 1;
				}
			}
			// std::cout << "\n";
		}
	}

	// std::cout << "Cover: ";
	for (int i = 0; i < maxNum; i++) {
		if (!universalSet.at(i)) {
			// std::cout << i << " not covered\n";
			return false;
		}
		else {
			// std::cout << i << " ";
		}
	}
	// std::cout << "\n";
	return true;
}


//Calculate the number of sets being used in the set.
int solutionSize(std::array<int, MAX_SIZE> subsetIndexes) {
	int size = 0;

	for (int i = 0; i < MAX_SIZE; i++) {
		size += subsetIndexes.at(i);
	}

	return size;
}

//Create a hash for the current solution, insert it into a table.
//Returns true if the solution has not yet been inserted, false
//otherwise.
bool isNew(std::array<int, MAX_SIZE> solution) {
	std::string vecToString;
	for (int i = 0; i < numSets; i++) {
        vecToString += solution.at(i);
	}

	int hash = hash_func(vecToString);
	bool exists = previousSolutions.find(hash) != previousSolutions.end();
	if (exists) {
		return false;
	}
	previousSolutions.insert(hash);
	return true;
}

//Applies the selected subset to the covering set.
void applySubset(std::array<int, MAX_SIZE> set, std::array<int, MAX_SIZE> &covered){
    for(int i = 0; i < MAX_SIZE; i++)
    {
        covered.at(i) += set.at(i);
    }
}

//Unapplies the selected subset from the covering set.
void unapplySubset(std::array<int, MAX_SIZE> set, std::array<int, MAX_SIZE> &covered){
    for(int i = 0; i < MAX_SIZE; i++)
    {
        covered.at(i) -= set.at(i);;
    }
}

//Finds the minimum set cover for a universe.
void getMinimumSetCoverIndexes(int index,
		std::array<int, MAX_SIZE> subsetIndexes,
		std::array<int, MAX_SIZE> covered, int depth) {

    // std::cout << "depth: " << depth << "\n";
    // printSet(subsetIndexes);
    // printBitVector(covered);

    //Do not continue if we've already looked at this solution.
    if (index > 0 && !isNew(subsetIndexes)) {
    	// std::cout << "Not new. Returning.\n";
    	return;
    }

    //Don't try to find solutions worse than the best so far
    if (depth >= bestSoFar) {
    	return;
    }

    //If we've already included this index in our set, go to the next one.
    while(covered.at(index) != 0) {
        index++;
    }

    //Once we reach the end of the list.
    if (index == maxNum) {
        // std::cout << "All numbers have been inserted into the cover." << std::endl;
        //Calculate the size of this solution.
        int size = solutionSize(subsetIndexes);
        // std::cout << "Solution size: " << size << std::endl;

        //If this is the best cover so far, print it.
        if (fullCover(subsetIndexes) && size < bestSoFar) {
            bestSoFar = size;
            std::cout << "(" << size << ") ";
            for (int i = 0; i < MAX_SIZE; i++) {
                if (subsetIndexes.at(i)) {
                    std::cout << i+1 << " ";
                }
            }
            std::cout << "\n";
        }
        return;
    }

    // std::cout << "Looking for a set containing: " << index+1 << std::endl;
    int i = 0;
    while(i < numSets){
		if (!subsetIndexes.at(i) && sets.at(i).at(index)) {
            // printSet(sets.at(i));
			subsetIndexes.at(i) = 1;
            applySubset(sets.at(i), covered);
			getMinimumSetCoverIndexes(index+1, subsetIndexes, covered, depth+1);
            unapplySubset(sets.at(i), covered);
			subsetIndexes.at(i) = 0;
		}
        i++;
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
	std::array<int, MAX_SIZE> subsetIndexes;
	subsetIndexes.fill(0);
	std::array<int, MAX_SIZE> covered;
	covered.fill(0);
	bestSoFar = MAX_SIZE;
	getMinimumSetCoverIndexes(0, subsetIndexes, covered, 0);

	double end_time = get_current_time();
	std::cout << "Execution time (s): " << (end_time - start_time) << "\n";

	return 0;
}
