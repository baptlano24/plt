#include "Square.h"
#include "SquareID.h"
using namespace state;
using namespace std;

Square::Square(): empty(1), id(EARTH) {}

Square::Square(bool empty, SquareID id): empty(empty), id(id) {}

bool Square:: isEmpty()
{
  return this->empty;
};

SquareID Square:: getID()
{
    return this->id;
};

void Square:: setID(SquareID newID)
{
  this->id = newID;
}

void Square:: setEmpty(bool empty)
{
  this->empty = empty;
}
