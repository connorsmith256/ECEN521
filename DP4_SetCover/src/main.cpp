#include <array>
#include <fstream>
#include <iostream>
#include <set>
#include <stdio.h>
#include <string>
#include <sstream>
#include <sys/time.h>
#include <unordered_map>
#include <vector>

#define MAX_NUM 1000
#define MAX_SOL_SIZE 100

std::vector<std::array<int, MAX_NUM> > sets;
int maxNum;
int numSets;
int bestSoFar;

void printLabel(std::string label) {
	std::string dashes("-------------------------------");
	std::cout << dashes << "\n" << label <<	"\n" << dashes << "\n";
}

void printBitVector(std::array<int, MAX_NUM> vec) {
	for (int i = 0; i < maxNum; i++) {
		if (vec.at(i)) {
			std::cout << i+1 << " ";
		}
	}
	std::cout << "\n";
}

// std::set<int> setUnion(const std::set<int> s1, const std::set<int> s2) {
// 	std::set<int> result = s1;
// 	result.insert(s2.begin(), s2.end());
// 	return result;
// }

// bool isCover(std::set<int> s, int maxNum) {
// 	return s.size() == maxNum;
// }

// bool isSolution(std::vector<int> subsetIndexes) {
// 	std::vector<int> contains(maxNum, 0);
// 	for (std::vector<int>::iterator I = subsetIndexes.begin(),
// 			IE = subsetIndexes.end(); I != IE; I++) {
// 		std::set<int> curSet = sets.at(*I);
// 		for (std::set<int>::iterator J = curSet.begin(), JE = curSet.end();
// 				J != JE; J++) {
// 			contains.at(*J-1) |= 1;
// 		}
// 	}

// 	int sum = 0;
// 	for (int i = 0; i < maxNum; i++) {
// 		sum += contains.at(i);
// 	}

// 	return sum == maxNum;
// }

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
		std::array<int, MAX_NUM> newArray;
		newArray.fill(0);

		int num;
		while (ss >> num) {
			newArray.at(num-1) = 1;
		}
		sets.push_back(newArray);
	}
}

// bool processSubset(std::vector<int> subsetIndexes) {
// 	if (isSolution(subsetIndexes)) {
// 		std::cout << subsetIndexes.size() << "\n";
// 		for (std::vector<int>::iterator I = subsetIndexes.begin(),
// 				IE = subsetIndexes.end(); I != IE; I++) {
// 			std::cout << "(" << (*I+1) << ") ";
// 			printBitVector(sets.at(*I));
// 		}
// 		std::cout << "\n";
// 		return true;
// 	}
// 	return false;
// }

// bool processSubsets(std::vector<int> supersetIndexes, int k, int startIndex,
// 		std::vector<int> subsetIndexes) {
// 	if (subsetIndexes.size() == k) {
// 		return processSubset(subsetIndexes);
// 	}
// 	if (startIndex == supersetIndexes.size()) {
// 		return false;
// 	}
// 	int next = supersetIndexes.at(startIndex);
// 	subsetIndexes.push_back(next);
// 	if (processSubsets(supersetIndexes, k, startIndex+1, subsetIndexes)) {
// 		return true;
// 	}
// 	subsetIndexes.pop_back();
// 	if (processSubsets(supersetIndexes, k, startIndex+1, subsetIndexes)) {
// 		return true;
// 	}
// 	return false;
// }

// bool fullCover(std::array<int, MAX_NUM> covered) {
// 	for (int i = 0; i < maxNum; i++) {
// 		if (!covered[i]) {
// 			std::cout << i+1 << " not covered\n";
// 			return false;
// 		}
// 	}

// 	return true;
// }

bool fullCover(std::array<int, MAX_SOL_SIZE> subsetIndexes) {
	std::array<int, MAX_NUM> universalSet;
	universalSet.fill(0);

	for (int i = 0; i < MAX_SOL_SIZE; i++) {
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

int solutionSize(std::array<int, MAX_SOL_SIZE> subsetIndexes) {
	int size = 0;

	for (int i = 0; i < MAX_SOL_SIZE; i++) {
		size += subsetIndexes.at(i);
	}

	return size;
}

std::set<int> previousSolutions;

bool isNew(std::array<int, MAX_SOL_SIZE> solution) {
	int hash = 0;
	for (int i = 0; i < MAX_SOL_SIZE; i++) {
		hash = hash*10 + solution.at(i);
	}

	std::cout << hash << "\n";

	bool found = previousSolutions.find(hash) != previousSolutions.end();
	if (!found) {
		previousSolutions.insert(hash);
		std::cout << "not found, inserting " << hash << "\n";
	}
	return found;
}

void getMinimumSetCoverIndexes(int index,
		std::array<int, MAX_SOL_SIZE> subsetIndexes,
		std::array<int, MAX_NUM> covered) {
	 if (!isNew(subsetIndexes)) {
	 	return;
	 }

	// std::cout << "index = " << index << ", size = " << solutionSize(subsetIndexes) << ", indexes = ";
	// for (int i = 0; i < MAX_SOL_SIZE; i++) {
	// 	if (subsetIndexes.at(i)) {
	// 		std::cout << i << " ";
	// 	}
	// }
	// std::cout << "\n";

	if (index == maxNum) {
		int size = solutionSize(subsetIndexes);
		if (fullCover(subsetIndexes) && size < bestSoFar) {
			bestSoFar = size;
			std::cout << "(" << size << ") ";
			for (int i = 0; i < MAX_SOL_SIZE; i++) {
				if (subsetIndexes.at(i)) {
					std::cout << i+1 << " ";
				}
			}
			std::cout << "\n";
		}
		return;
	}

	for (int i = 0; i < numSets; i++) {
		if (!subsetIndexes.at(i) && sets.at(i).at(index)) {
			subsetIndexes.at(i) = 1;
			getMinimumSetCoverIndexes(index+1, subsetIndexes, covered);
			subsetIndexes.at(i) = 0;
			getMinimumSetCoverIndexes(index+1, subsetIndexes, covered);
		}
	}

	// std::vector<int> minimumIndexes;
	// std::vector<int> curIndexes;
	// bool foundSolution = false;

	// std::vector<int> allIndexes;
	// for (int i = 0; i < numSets; i++) {
	// 	allIndexes.push_back(i);
	// }

	// for (int i = 1; i <= numSets; i++) {
	// 	// test all solutions of size i
	// 	std::cout << i << "\n";
	// 	curIndexes.clear();
	// 	foundSolution = processSubsets(allIndexes, i, 0, curIndexes);
	// 	if (foundSolution) {
	// 		break;
	// 	}
	// }
}

int main(int argc, char* argv[]) {
	std::string fileName(argv[1]);
	processHeader(fileName.c_str());

	printLabel("Max number, number of sets:");
	std::cout << maxNum << "\n" << numSets << "\n";

	getSets(fileName.c_str());
	printLabel("Input sets:");
	for (std::vector<std::array<int, MAX_NUM> >::iterator I = sets.begin(),
			IE = sets.end(); I != IE; I++) {
		std::cout << "(" << (I - sets.begin() + 1) << ") ";
		printBitVector(*I);
	}

	printLabel("Results:");

	std::array<int, MAX_SOL_SIZE> subsetIndexes;
	subsetIndexes.fill(0);
	std::array<int, MAX_NUM> covered;
	covered.fill(0);
	bestSoFar = MAX_NUM;
	getMinimumSetCoverIndexes(0, subsetIndexes, covered);

	return 0;
}
