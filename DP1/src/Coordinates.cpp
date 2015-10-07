
#include "Coordinates.hpp"

Cartesian::Cartesian(double x_c, double y_c)
{
	this->x = x_c;
	this->y = y_c;
}

void Cartesian::Print()
{
	std::cout.precision(15);
	std::cout << this->x << "," << this->y << std::endl;
}

double Cartesian::Get_X()
{
	return this->x;
}

double Cartesian::Get_Y()
{
	return this->y;
}

void Cartesian::Set(double x_c, double y_c)
{
	this->x = x_c;
	this->y = y_c;
}

void Cartesian::Set(Cartesian* c)
{
	this->x = c->Get_X();
	this->y = c->Get_Y();
}

void Cartesian::SetAngle(double rad)
{
	this->angle = rad;
}

double Cartesian::GetAngle()
{
	return this->angle;
}

bool Cartesian::operator> (Cartesian& that)
{
    std::cout << ">\n";
    return this->Get_X() < that.Get_X();
}

bool Cartesian::operator<= (Cartesian& that)
{
    std::cout << "<=\n";
    return this->Get_X() < that.Get_X();
}

bool Cartesian::operator< (Cartesian& that)
{
    std::cout << "<\n";
    return this->Get_X() < that.Get_X();
}

bool Cartesian::operator>= (Cartesian& that)
{
    std::cout << ">=\n";
    return this->Get_X() < that.Get_X();
}
