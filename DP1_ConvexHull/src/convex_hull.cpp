/*
 * convex_hull.cpp
 *
 *  Created on: Oct 2, 2015
 *      Author: Matthew James, Matthew Wyman, and Connor Smith
 */


#include "convex_hull.hpp"

using namespace std;

//Quickhull algorithm
//If there are only three points, these are the hull.
//If there are more, use the max/min x and y, these will be part of the hull.
//Discard all points inside the temporary hull.
//Find the points that have the maximum distance between the lines drawn between the four points.
//Repeat until you're done.
Convex_Hull::Convex_Hull(vector<Cartesian*> pointList, int pointCount)
{
	this->pointCount = pointCount;
	this->pointList = pointList;
}

std::pair<Cartesian*, Cartesian*> Convex_Hull::GetExtrema() {
	// cout << "Input Coordinates:" << endl;
	Cartesian *minimum = new Cartesian(0,0);
	Cartesian *maximum = new Cartesian(0,0);
	vector<Cartesian*>::iterator iterator = pointList.begin();
	minimum->Set(*iterator);
	maximum->Set(*iterator);

	for (vector<Cartesian*>::const_iterator iterator = pointList.begin(), end = pointList.end(); iterator != end; ++iterator)
	{
		double curx,cury;
		curx = (*iterator)->Get_X();
		cury = (*iterator)->Get_Y();
		if (curx > maximum->Get_X() || (curx == maximum->Get_X() && cury > maximum->Get_Y()))
		{
			maximum->Set(curx,cury);
		}

		if (curx < minimum->Get_X() || (curx == minimum->Get_X() && cury < minimum->Get_Y()))
		{
			minimum->Set(curx,cury);
		}

		// (*iterator)->Print();
	}

	return std::pair<Cartesian*, Cartesian*> (minimum, maximum);
}

void Convex_Hull::ComputeHull()
{
	std::pair<Cartesian*, Cartesian*> extrema = GetExtrema();
	Cartesian* minimum = extrema.first;
	minxpoint = minimum->Get_X();
	minypoint = minimum->Get_Y();
	Cartesian* maximum = extrema.second;
	//cout << "Done finding min and max points." << endl;

	//Shortcut, if there are only three points, they all must be in the convex hull.
	if (this->pointCount == 3) {
		this->hullList = this->pointList;
		return;
	}

	//cout << "These two points are the extrema on the x axis." << endl;
	//minimum->Print();
	//maximum->Print();

	this->hullList.push_back(minimum);
	this->hullList.push_back(maximum);

	//If there is no variation in X, I'm not really sure how you solve this, but I have the highest Y and lowest Y selected.
	if (minimum->Get_X() == maximum->Get_X())
	{
		return;
	}

	//Divide the list in two. Points above the line between minimum and maximum and points below.
	vector<Cartesian*> top;
	vector<Cartesian*> bottom;
	double minx, miny, maxx, maxy;
	minx = minimum->Get_X();
	miny = minimum->Get_Y();
	maxx = maximum->Get_X();
	maxy = maximum->Get_Y();

	double slope = (maxy - miny) / (maxx - minx);
	for(vector<Cartesian*>::const_iterator iterator = pointList.begin(), end = pointList.end(); iterator != end; ++iterator)
	{
		double curx = (*iterator)->Get_X();
		double cury = (*iterator)->Get_Y();
		double line_y = slope*(curx-minx)+miny;
		if (cury > line_y)
		{
			top.push_back(*iterator);
		}
		else if (cury < line_y)
		{
			bottom.push_back(*iterator);
		}

	}

	QuickHull(bottom, new Line(minimum,maximum));
	QuickHull(top, new Line(minimum,maximum));
}

void Convex_Hull::QuickHull(const vector<Cartesian*> &outsideList, Line* line)
{
	if (outsideList.empty())
		return;
	Cartesian* farthest_point;
	double max_distance = 0;
	double current_distance = 0;
	for (vector<Cartesian*>::const_iterator iterator = outsideList.begin(), end = outsideList.end(); iterator != end; ++iterator)
	{
		// cout << "considering point ";
		// (*iterator)->Print();

		current_distance = line->Distance(*iterator);
		if (current_distance > max_distance)
		{
			max_distance = current_distance;
			farthest_point = (*iterator);
		}
	}

	// cout << "farthest point: ";
	// farthest_point->Print();
	this->hullList.push_back(farthest_point);

	Triangle* triangle = new Triangle(line, farthest_point);

	// cout << "---- up\n";
	vector<Cartesian*> outside_set_1 = triangle->CalcOutSidePoints(outsideList,true);
	QuickHull(outside_set_1, new Line(line->GetPoints().first, farthest_point));

	// cout << "---- down\n";
	vector<Cartesian*> outside_set_2 = triangle->CalcOutSidePoints(outsideList,false);
	QuickHull(outside_set_2, new Line(line->GetPoints().second, farthest_point));
}

bool compare(Cartesian* left, Cartesian* right) {
	return (left->GetAngle() < right->GetAngle());
}

void Convex_Hull::PrintHullList()
{
	// cout << "The Convex Hull is..." << endl;
	vector<Cartesian*> finalList;
		
	//reference everything to the minimimum point.
	//data will be sorted with the minimum point as reference, values of atan2 go from -pi to pi
	//but remember, since we're using the minx and miny point as reference, no values will be past -pi/2 or pi/2
	for(vector<Cartesian*>::iterator iterator = hullList.begin(), end = hullList.end(); iterator != end; ++iterator)
	{
		finalList.push_back(*iterator);
		double temp_x,temp_y;
		
		temp_x = (*iterator)->Get_X();
		temp_y = (*iterator)->Get_Y();
		if (temp_x == minxpoint && temp_y == minypoint)
			(*iterator)->SetAngle(-10); //Just needs to be less than -pi to sort correctly!
		else		
			(*iterator)->SetAngle(atan2(temp_y,temp_x));		
	}

	sort(finalList.begin(), finalList.end(), compare);
	for (vector<Cartesian*>::iterator iterator = finalList.begin(), end = finalList.end(); iterator != end; ++iterator) {
		(*iterator)->Print();
	}
}
