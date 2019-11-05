#include "Coord.h"
#include <iostream>
using namespace std;
using namespace state;

Coord::Coord(int x, int y): x(x),y(y){}

Coord::Coord(){
    Coord(0,0);
}

int Coord::getX()
{
    return this->x;
}

int Coord::getY()
{
    return this->y;
}

void Coord::setY(int y)
{
    this->y = y;
}

void Coord::setX(int x)
{
    this->x = x;
}
