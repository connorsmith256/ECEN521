/*
 * Line.cpp
 *
 *  Created on: Oct 2, 2015
 *      Author: Matthew James and Connor Smith
 */



#include "Line.hpp"

Line::Line(Cartesian *p0, Cartesian *p1)
{
	this->p0 = p0;
	this->p1 = p1;
}

double Line::Distance(Cartesian *p2)
{
	double minx, miny, maxx, maxy, x, y;
	minx = this->p0->Get_X();
	miny = this->p0->Get_Y();
	maxx = this->p1->Get_X();
	maxy = this->p1->Get_Y();
	x = p2->Get_X();
	y = p2->Get_Y();
	double distance;
	distance = fabs((maxy-miny)*x - (maxx-minx)*y + maxx*miny -maxy*minx) / sqrt( pow((maxy-miny),2) + pow((maxx-minx),2) );

	return distance;
}

std::pair<Cartesian*, Cartesian*> Line::GetPoints()
{
	std::pair<Cartesian*, Cartesian*> my_pair;
	my_pair.first = this->p0;
	my_pair.second = this->p1;
	return my_pair;
}




