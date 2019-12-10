#include "../state/State.h"
#include "DeepAI.h"
#include "engine.h"
#include <unistd.h>
#include <iostream>
#include <math.h>

using namespace std;
using namespace state;
using namespace engine;
using namespace ai;


DeepAI::DeepAI(int color, engine::Engine* engine){
  this->color = color;
  this->map = &engine->getState().getGrid();
}

void DeepAI::play(engine::Engine* engine) {

}

int DeepAI::getDistance(Coord& coord1, Coord& coord2){
  int distance;
  distance = abs(coord2.getX()-coord1.getX())+abs(coord2.getY()-coord1.getY());
  return distance;
}
