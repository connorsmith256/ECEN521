//This program was created by Matthew James
//October 2, 2015
//All rights reserved

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

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

	ifstream inFile;
	inFile.open(argv[1], ios::in);
	if (inFile.is_open())
	{
		vector<Cartesian*> point_list;
		int point_count = 0;
		while (inFile.good() && !inFile.eof())
		{
			string s;
			getline(inFile, s);

			if (inFile.eof()) {
				break;
			}

			stringstream ss(s);
			double x,y;
			ss >> x;
			ss.get();
			ss >> y;
			point_list.push_back(new Cartesian(x,y));
			point_count++;
		}
		inFile.close();

		Convex_Hull hull(point_list,point_count);
		hull.ComputeHull();
		hull.PrintHullList();
		return 0;
	}
	else
		cout << "Unable to open file!" << endl;
	return 1;
}



