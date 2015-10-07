/*
 * Triangle.cpp
 *
 *  Created on: Oct 2, 2015
 *      Author: ecestudent
 */

#include "Triangle.hpp"

Triangle::Triangle(Line* l, Cartesian* c)
{
	std::pair<Cartesian*, Cartesian*> my_pair = l->GetPoints();
	this->p0 = my_pair.first;
	this->p1 = my_pair.second;
	this->p2 = c;
}

std::vector<Cartesian*> Triangle::CalcOutSidePoints(const std::vector<Cartesian*> &old_list, bool switch_AC)
{
	std::vector<Cartesian*> outside_list;

	double ax,ay,bx,by,cx,cy,px,py,cp1,cp2;
	if (switch_AC)
	{
		ax = this->p0->Get_X();
		ay = this->p0->Get_Y();
		cx = this->p1->Get_X();
		cy = this->p1->Get_Y();
	}
	else
	{
		ax = this->p1->Get_X();
		ay = this->p1->Get_Y();
		cx = this->p0->Get_X();
		cy = this->p0->Get_Y();
	}

	bx = this->p2->Get_X();
	by = this->p2->Get_Y();

	cp1 = (bx-ax)*(cy-ay)-(by-ay)*(cx-ax); //caclulate X product of AB,AC

	for (std::vector<Cartesian*>::const_iterator iterator = old_list.begin(), end = old_list.end(); iterator != end; ++iterator)
	{
		px = (*iterator)->Get_X();
		py = (*iterator)->Get_Y();

		cp2 = (bx-ax)*(py-ay)-(by-ay)*(px-ax); //caclulate X product of AB,AP
		// std::cout << "Cross Product: " << cp1 << " " << cp2 << std::endl;

		if ((cp1 > 0 && cp2 < 0) || (cp1 < 0 && cp2 > 0))
		{
			// std::cout << "Adding: ";
			// (*iterator)->Print();
			outside_list.push_back(*iterator);
		}
	}
	return outside_list;
}
