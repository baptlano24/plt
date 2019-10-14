#include "Square.h"
#include "SquareID.h"
#include namespace state;
#include namespace std;

Square::Square(bool empty, SquareID id): empty(empty), id(id) {}

bool Square:: isEmpty()
{
  return this->empty;
};

SquareId Square:: getID()
{
    return this->id;
};
