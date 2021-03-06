#include "../state/State.h"
#include "NoviceAI.h"
#include "RandomAI.h"
#include "engine.h"
#include <unistd.h>
#include <iostream>
#include <math.h>

using namespace std;
using namespace state;
using namespace engine;
using namespace ai;


NoviceAI::NoviceAI(int color){
  this->color = color;
}

Move NoviceAI::play(engine::Engine* engine) {

  bool animalSelectedIA = false;
  Coord targetCoord;
  Coord& refTargetCoord = targetCoord;
  Animal* selectedAnimal;

  if (animalSelectedIA == false) {
    cout << "Selection IA:" << endl;
    pair<Animal*, int> selectionIA = this->selectAnimal(engine);
    selectedAnimal = selectionIA.first;
    Select selectIA(selectedAnimal, selectedAnimal->getCoord(), this->color);
    animalSelectedIA = true;

  }
  if ((animalSelectedIA == true)) {
    cout << "-- Beginning of the IA Novice move --" << endl;
    std::pair<state::Coord,engine::ActionID> action = this->selectAction(engine, selectedAnimal->getCoord());
    targetCoord.setX(action.first.getX());
    targetCoord.setY(action.first.getY());
    engine::Move moveIA(selectedAnimal, refTargetCoord, this->color);
    animalSelectedIA = false;
    cout << "-- End of the IA move --" << endl;
    return moveIA;
  }
}

std::pair<state::Coord,engine::ActionID> NoviceAI::selectAction(engine::Engine* engine, Coord& current_square){
  std::pair<state::Coord,engine::ActionID> action;
  std::vector<std::pair<state::Coord,engine::ActionID>> authorisedActions = engine->authorisedActions(engine->getState(),current_square);

  Coord ObjectifJ1(6,12);
  Coord ObjectifJ2(5,0);
  double dmin = 100;
  pair<state::Coord,engine::ActionID> actionSelected;

  if(this->color == 0){
    for(int i=0; i<4; i++){
      double distance = getDistance(authorisedActions[i].first, ObjectifJ1);
      if(distance < dmin && authorisedActions[i].second != NONE) {
        dmin = distance;
        actionSelected = authorisedActions[i];
      }
    }
  } else if (this->color == 1){
    for(int i=0; i<4; i++){
      double distance = getDistance(authorisedActions[i].first, ObjectifJ2);
      if(distance < dmin && authorisedActions[i].second != NONE) {
        dmin = distance;
        actionSelected = authorisedActions[i];
      }
    }
  }
  return actionSelected;
}

pair<state::Animal*, int> NoviceAI::selectAnimal(engine::Engine* engine)
{
  RandomAI randomAI(this->color);
  return randomAI.selectRandomAnimal(engine);


  /*pair<Animal*, int> selection;
  Coord ObjectifJ1(5,0);
  Coord ObjectifJ2(6,12);
  double dmax = 0;
  //vector<pair<Animal*,float>> distances;
  Animal* animalSelected;
  Animal* animal;
  if(this->color == 0){
    for(int i=0; i<8; i++){
      animal = &engine->getState().getPlayer1().getAnimals()[i];
      Coord& animalCoord = animal->getCoord();
      double distance = getDistance(animalCoord, ObjectifJ2);
      //distances.push_back(make_pair(animal,distance));
      if((distance > dmax || animalSelected->getID()< animal->getID()) && animal->getStatus() != DEAD) {
        dmax = distance;
        animalSelected = animal;
      }
      cout << "distance Objectif-position actuelle " << distance << endl;
    }
  } else if (this->color == 1){
    for(int i=0; i<8; i++){
      animal = &engine->getState().getPlayer2().getAnimals()[i];
      Coord& animalCoord = animal->getCoord();
      double distance = getDistance(animalCoord, ObjectifJ1);
      //distances.push_back(make_pair(animal,distance));
      if((distance > dmax || animalSelected->getID()< animal->getID()) && animal->getStatus() != DEAD) {
        dmax = distance;
        animalSelected = animal;
      }
      cout << "distance Objectif-position actuelle " << distance << endl;
    }
  }
  selection = make_pair(animalSelected, this->color);
  return selection;*/
}


double NoviceAI::getDistance(Coord& coord1, Coord& coord2){
  double distance;
  distance = sqrt(pow((coord2.getX()-coord1.getX()),2)+pow((coord2.getY()-coord1.getY()),2));
  return distance;
}
