#include <fstream>
#include <iostream>
#include <set>
#include <stdio.h>
#include <string>
#include <sstream>
#include <sys/time.h>
#include <vector>

void print_label(std::string label) {
	std::string dashes("-------------------------------");
	std::cout << dashes << "\n" << label <<	"\n" << dashes << "\n";
}

void print_set(std::set<int> s) {
	for (std::set<int>::iterator I = s.begin(), IE = s.end(); I != IE; I++) {
		std::cout << *I << " ";
	}
	std::cout << "\n";
}

std::set<int> set_union(const std::set<int> s1, const std::set<int> s2) {
	std::set<int> result = s1;
	result.insert(s2.begin(), s2.end());
	return result;
}

bool is_cover(std::set<int> s, int max_num) {
	return s.size() == max_num;
}

std::pair<int, int> getHeader(const char* file_name) {
	std::pair<int, int> header;
	std::ifstream fstream(file_name);
	fstream >> header.first >> header.second;
	return header;
}

std::vector<std::set<int> > getSets(const char* file_name, int num_sets) {
	std::vector<std::set<int> > sets;
	std::ifstream fstream(file_name);
	std::string line;
	getline(fstream, line);
	getline(fstream, line);

	for (int i = 0; i < num_sets; i++) {
		getline(fstream, line);
		std::istringstream ss(line);
		std::set<int> new_set;
		int num;

		while (ss >> num) {
			new_set.insert(num);
		}
		sets.push_back(new_set);
	}

	return sets;
}

std::vector<int> getMinimumSetCoverIndexes(std::vector<std::set<int> > sets,
		int max_num) {
	std::vector<int> minimumIndexes;
	bool foundSolution = false;

	int num_sets = sets.size();
	for (int i = 1; i <= num_sets; i++) {
		if (foundSolution) {
			break;
		}
		// test all solutions of size i
	}

	minimumIndexes.push_back(2);
	minimumIndexes.push_back(3);
	minimumIndexes.push_back(4);

	return minimumIndexes;
}

int main(int argc, char* argv[]) {
	std::string file_name(argv[1]);
	std::pair<int, int> header = getHeader(file_name.c_str());
	int max_num = header.first;
	int num_sets = header.second;

	print_label("Max number, number of sets:");
	std::cout << max_num << "\n" << num_sets << "\n";

	std::vector<std::set<int> > sets = getSets(file_name.c_str(), num_sets);
	print_label("Input sets:");
	for (std::vector<std::set<int> >::iterator I = sets.begin(),
			IE = sets.end(); I != IE; I++) {
		print_set(*I);
	}

	print_label("Results:");
	std::vector<int> minimumIndexes = getMinimumSetCoverIndexes(sets, num_sets);
	std::cout << minimumIndexes.size() << "\n";
	for (std::vector<int>::iterator I = minimumIndexes.begin(),
			IE = minimumIndexes.end(); I != IE; I++) {
		std::cout << "(" << *I << ") ";
		print_set(sets.at(*I));
	}

	return 0;
}
