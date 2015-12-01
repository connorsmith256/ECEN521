#include <fstream>
#include <iostream>
#include <set>
#include <stdio.h>
#include <string>
#include <sstream>
#include <sys/time.h>
#include <vector>

std::vector<std::set<int> > sets;
int maxNum;
int numSets;

void printLabel(std::string label) {
	std::string dashes("-------------------------------");
	std::cout << dashes << "\n" << label <<	"\n" << dashes << "\n";
}

void printSet(std::set<int> s) {
	for (std::set<int>::iterator I = s.begin(), IE = s.end(); I != IE; I++) {
		std::cout << *I << " ";
	}
	std::cout << "\n";
}

std::set<int> setUnion(const std::set<int> s1, const std::set<int> s2) {
	std::set<int> result = s1;
	result.insert(s2.begin(), s2.end());
	return result;
}

bool isCover(std::set<int> s, int maxNum) {
	return s.size() == maxNum;
}

bool isSolution(std::vector<int> subsetIndexes) {
	std::vector<int> contains(maxNum, 0);
	for (std::vector<int>::iterator I = subsetIndexes.begin(),
			IE = subsetIndexes.end(); I != IE; I++) {
		std::set<int> curSet = sets.at(*I);
		for (std::set<int>::iterator J = curSet.begin(), JE = curSet.end();
				J != JE; J++) {
			contains.at(*J-1) |= 1;
		}
	}

	int sum = 0;
	for (int i = 0; i < maxNum; i++) {
		sum += contains.at(i);
	}

	return sum == maxNum;
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
		std::set<int> newSet;
		int num;

		while (ss >> num) {
			newSet.insert(num);
		}
		sets.push_back(newSet);
	}
}

bool processSubset(std::vector<int> subsetIndexes) {
	if (isSolution(subsetIndexes)) {
		std::cout << subsetIndexes.size() << "\n";
		for (std::vector<int>::iterator I = subsetIndexes.begin(),
				IE = subsetIndexes.end(); I != IE; I++) {
			std::cout << "(" << (*I+1) << ") ";
			printSet(sets.at(*I));
		}
		std::cout << "\n";
		return true;
	}
	return false;
}

bool processSubsets(std::vector<int> supersetIndexes, int k, int startIndex,
		std::vector<int> subsetIndexes) {
	if (subsetIndexes.size() == k) {
		return processSubset(subsetIndexes);
	}
	if (startIndex == supersetIndexes.size()) {
		return false;
	}
	int next = supersetIndexes.at(startIndex);
	subsetIndexes.push_back(next);
	if (processSubsets(supersetIndexes, k, startIndex+1, subsetIndexes)) {
		return true;
	}
	subsetIndexes.pop_back();
	if (processSubsets(supersetIndexes, k, startIndex+1, subsetIndexes)) {
		return true;
	}
	return false;
}

void getMinimumSetCoverIndexes() {
	std::vector<int> minimumIndexes;
	std::vector<int> curIndexes;
	bool foundSolution = false;

	std::vector<int> allIndexes;
	for (int i = 0; i < numSets; i++) {
		allIndexes.push_back(i);
	}

	for (int i = 1; i <= numSets; i++) {
		// test all solutions of size i
		curIndexes.clear();
		foundSolution = processSubsets(allIndexes, i, 0, curIndexes);
		if (foundSolution) {
			break;
		}
	}
}

int main(int argc, char* argv[]) {
	std::string fileName(argv[1]);
	processHeader(fileName.c_str());

	printLabel("Max number, number of sets:");
	std::cout << maxNum << "\n" << numSets << "\n";

	getSets(fileName.c_str());
	printLabel("Input sets:");
	for (std::vector<std::set<int> >::iterator I = sets.begin(),
			IE = sets.end(); I != IE; I++) {
		std::cout << "(" << (I - sets.begin() + 1) << ") ";
		printSet(*I);
	}

	printLabel("Results:");
	getMinimumSetCoverIndexes();

	return 0;
}
