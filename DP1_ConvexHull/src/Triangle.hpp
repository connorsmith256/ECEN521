/*
 * Triangle.hpp
 *
 *  Created on: Oct 2, 2015
 *      Author: ecestudent
 */

#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_

#include <vector>
#include "Line.hpp"
#include "Coordinates.hpp"
#include <stdlib.h>

class Triangle
{
private:
	Cartesian* p0;
	Cartesian* p1;
	Cartesian* p2;
public:
	Triangle(Line*, Cartesian*);
	std::vector<Cartesian*> CalcOutSidePoints(const std::vector<Cartesian*> &old_list, bool);
};



#endif /* TRIANGLE_HPP_ */
