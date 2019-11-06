#include "../state/State.h"
#include "Engine.h"
#include "Order.h"
#include "Move.h"
#include <iostream>
using namespace std;
using namespace state;
using namespace engine;


Move::Move(state::Animal target, state::Coord destination):target(target),destination(destination){
    this->ID = MOVE;
    this->player = 0;
}


void Move::execute(state::State state)
{
  if (this->target.getStatus()==NORMAL)
  {
    this->target.setCoord(this->destination);
  }
}
