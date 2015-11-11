/*
 * Line.hpp
 *
 *  Created on: Oct 2, 2015
 *      Author: Matthew James and Connor Smith
 */

#ifndef LINE_HPP_
#define LINE_HPP_

#include <cmath>
#include "Coordinates.hpp"

class Line
{
private:
	Cartesian* p0;
	Cartesian* p1;
public:
	Line(Cartesian*, Cartesian*);
	double Distance(Cartesian*);
	std::pair<Cartesian*, Cartesian*> GetPoints();
};




#endif /* LINE_HPP_ */
