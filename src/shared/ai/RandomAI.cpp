#include "../state/State.h"
#include "RandomAI.h"
#include "engine.h"
#include <unistd.h>
#include <iostream>

using namespace std;
using namespace state;
using namespace engine;
using namespace ai;

RandomAI::RandomAI(int color){
  this->color = color;
}

Move RandomAI::play(Engine* engine) {

  bool animalSelectedIA = false;
  Coord targetCoord;
  Coord& refTargetCoord = targetCoord;
  Animal* selectedAnimal;

  if (animalSelectedIA == false) {
    cout << "Selection IA:" << endl;
    pair<Animal*, int> selectionIA = this->selectRandomAnimal(engine);
    selectedAnimal = selectionIA.first;
    Select selectIA(selectedAnimal, selectedAnimal->getCoord(), this->color);
    animalSelectedIA = true;

  }
  if ((animalSelectedIA == true)) {
    cout << "-- Beginning of the IA move --" << endl;
    pair<Coord,ActionID> randAction = this->randomAction(engine, selectedAnimal->getCoord());
    targetCoord.setX(randAction.first.getX());
    targetCoord.setY(randAction.first.getY());
    Move moveIA(selectedAnimal, refTargetCoord, this->color);
    animalSelectedIA = false;
    cout << "-- End of the IA move --" << endl;
    return moveIA;
  }
}

pair<Coord,ActionID> RandomAI::randomAction(Engine* engine, Coord& current_square){
  pair<Coord,ActionID> action;
  vector<pair<Coord,ActionID>> authorisedActions = engine->authorisedActions(engine->getState(),current_square);
  int random = rand() % 4;
  while (authorisedActions[random].second == NONE){
     random = rand() % 4;
  }
  action = authorisedActions[random];
  return action;
}

pair<Animal*, int> RandomAI::selectRandomAnimal(Engine* engine)
{
  pair<Animal*, int> selection;
  int random0_7 = rand() % 8;
  if (this->color == 0){
    while(engine->getState().getPlayer1().getAnimals()[random0_7].getStatus() == DEAD){
       random0_7 = rand() % 8;
    }
    selection.first = &engine->getState().getPlayer1().getAnimals()[random0_7];
  } else if (this->color == 1){
    while(engine->getState().getPlayer2().getAnimals()[random0_7].getStatus() == DEAD){
       random0_7 = rand() % 8;
    }
    selection.first = &engine->getState().getPlayer2().getAnimals()[random0_7];
  }
  selection.second =this->color;
  return selection;
}
