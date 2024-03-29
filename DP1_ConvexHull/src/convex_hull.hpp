/*
 * convex_hull.hpp
 *
 *  Created on: Oct 2, 2015
 *      Author: Matthew James
 */

#ifndef CONVEX_HULL_HPP_
#define CONVEX_HULL_HPP_

#include <iostream>
#include <vector>
#include <algorithm>
#include "Coordinates.hpp"
#include "Line.hpp"
#include "Triangle.hpp"

class Convex_Hull
{
private:
	int pointCount;
	std::vector<Cartesian*> pointList;
	std::vector<Cartesian*> hullList;
	std::pair<Cartesian*, Cartesian*> GetExtrema();
	double minxpoint;
	double minypoint;
	void QuickHull(const std::vector<Cartesian*> &outsideList, Line*);
public:
	Convex_Hull(std::vector<Cartesian*>, int);
	void ComputeHull();
	void PrintHullList();
};



#endif /* CONVEX_HULL_HPP_ */
