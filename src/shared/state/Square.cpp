#include "Square.h"
#include "SquareID.h"
using namespace state;
using namespace std;

Square::Square(bool empty, SquareID id): empty(empty), id(id) {}

bool Square:: isEmpty()
{
  return this->empty;
};

SquareID Square:: getID()
{
    return this->id;
};
