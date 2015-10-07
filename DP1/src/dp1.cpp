//This program was created by Matthew James
//October 2, 2015
//All rights reserved

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>
#include <stdio.h>

#include "Coordinates.hpp"
#include "convex_hull.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		cout << "Error: no input file specified." << endl;
		return 1;
	}

	FILE* f = fopen(argv[1], "r");
	if (f == NULL) {
		cout << "Unable to open file!\n";
		return 1;
	}

	vector<Cartesian*> point_list;
	char line[100];
	double x, y;
	int point_count = 0;

	while (fgets(line, 100, f)) {
		sscanf(line, "%lf,%lf", &x, &y);
		point_list.push_back(new Cartesian(x, y));
		point_count++;
	}

	Convex_Hull hull(point_list, point_count);
	hull.ComputeHull();
	hull.PrintHullList();

	return 0;
}



