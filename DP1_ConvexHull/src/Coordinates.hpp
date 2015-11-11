/*
 * convex_hull.hpp
 *
 *  Created on: Oct 2, 2015
 *      Author: Matthew James
 */

#ifndef COORDINATES_HPP_
#define COORDINATES_HPP_

#include <iostream>


class Cartesian
{
private:
	double x;
	double y;
	double angle;
public:
	Cartesian(double, double);
	void Print();
	double Get_X();
	double Get_Y();
	void Set(double,double);
	void Set(Cartesian*);
	void SetAngle(double);
	double GetAngle();
	bool operator> (Cartesian& that);
	bool operator<= (Cartesian& that);
	bool operator< (Cartesian& that);
	bool operator>= (Cartesian& that);
};


#endif /* COORDINATES_HPP_ */
