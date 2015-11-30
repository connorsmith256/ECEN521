#include <fstream>
#include <iostream>
#include <set>
#include <stdio.h>
#include <string>
#include <sstream>
#include <sys/time.h>
#include <vector>

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

int main(int argc, char* argv[]) {
	std::string file_name(argv[1]);
	std::ifstream input_file(file_name.c_str());

	int max_num, num_lines;
	input_file >> max_num >> num_lines;
	std::string line;
	getline(input_file, line);

	std::cout << "Max number: " << max_num << ", Number of sets:  " << num_lines << "\n";

	std::vector<std::set<int> > sets;
	for (int i = 0; i < num_lines; i++) {
		getline(input_file, line);
		std::istringstream ss(line);
		std::set<int> new_set;
		int num;

		while (ss >> num) {
			new_set.insert(num);
		}
		sets.push_back(new_set);
	}

	for (std::vector<std::set<int> >::iterator I = sets.begin(), IE = sets.end(); I != IE; I++) {
		std::cout << "Set: ";
		print_set(*I);
	}

	std::set<int> new_set = set_union(sets.at(2), sets.at(3));
	print_set(new_set);

	new_set = set_union(new_set, sets.at(4));
	print_set(new_set);

	std::cout << is_cover(new_set, max_num) << "\n";

	return 0;
}
