#include "../state/State.h"
#include "HeuristicAI.h"
#include "RandomAI.h"
#include "engine.h"
#include <unistd.h>
#include <iostream>
#include <math.h>

using namespace std;
using namespace state;
using namespace engine;
using namespace ai;


HeuristicAI::HeuristicAI(int color){
  this->color = color;
}

void HeuristicAI::play(engine::Engine* engine) {

  bool animalSelectedIA = false;
  Coord targetCoord;
  Coord& refTargetCoord = targetCoord;
  Animal* selectedAnimal;

  StateEvent animalChangedEvent(ANIMALS_CHANGED);
  StateEvent& refAnimalChangedEvent = animalChangedEvent;
  StateEvent highlightsChangedEvent(HIGHLIGHTS_CHANGED);
  StateEvent& refHighlightsChangedEvent = highlightsChangedEvent;
  StateEvent infosChangedEvent(INFOS_CHANGED);
  StateEvent& refInfosChangedEvent = infosChangedEvent;

  if (animalSelectedIA == false) {
    cout << "Selection IA:" << endl;
    pair<Animal*, int> selectionIA = this->selectAnimal(engine);
    selectedAnimal = selectionIA.first;
    Select selectIA(selectedAnimal, selectedAnimal->getCoord());
    selectIA.execute(engine);
    engine->getState().notifyObservers(refHighlightsChangedEvent, engine->getState());
    animalSelectedIA = true;

  }
  if ((animalSelectedIA == true)) {
    cout << "-- Beginning of the IA move --" << endl;
    cout << "Animal selected id: " << selectedAnimal->getID() << endl;
    std::pair<state::Coord,engine::ActionID> action = this->selectAction(engine, selectedAnimal->getCoord());
    targetCoord.setX(action.first.getX());
    targetCoord.setY(action.first.getY());
    engine::Move moveIA(selectedAnimal, refTargetCoord);
    moveIA.execute(engine);

    usleep(400000);
    engine->getState().notifyObservers(refAnimalChangedEvent, engine->getState());
    engine->getState().notifyObservers(refHighlightsChangedEvent, engine->getState());
    engine->getState().notifyObservers(refInfosChangedEvent, engine->getState());
    animalSelectedIA = false;
    cout << "-- End of the IA move --" << endl;
  }
}

std::pair<state::Coord,engine::ActionID> HeuristicAI::selectAction(engine::Engine* engine, Coord& current_square){
  std::pair<state::Coord,engine::ActionID> action;
  std::vector<std::pair<state::Coord,engine::ActionID>> authorisedActions = engine->authorisedActions(engine->getState(),current_square);

  Coord ObjectifJ1(5,0);
  Coord ObjectifJ2(6,12);
  double dmin = 100;
  pair<state::Coord,engine::ActionID> actionSelected;

  if(this->color == 0){
    for(int i=0; i<4; i++){
      double distance = getDistance(authorisedActions[i].first, ObjectifJ2);
      if(distance < dmin && authorisedActions[i].second != NONE) {
        dmin = distance;
        actionSelected = authorisedActions[i];
      }
    }
  } else if (this->color == 1){
    for(int i=0; i<4; i++){
      double distance = getDistance(authorisedActions[i].first, ObjectifJ1);
      if(distance < dmin && authorisedActions[i].second != NONE) {
        dmin = distance;
        actionSelected = authorisedActions[i];
      }
    }
  }
  return actionSelected;
}

pair<state::Animal*, int> HeuristicAI::selectAnimal(engine::Engine* engine)
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


double HeuristicAI::getDistance(Coord& coord1, Coord& coord2){
  double distance;
  distance = sqrt(pow((coord2.getX()-coord1.getX()),2)+pow((coord2.getY()-coord1.getY()),2));
  return distance;
}
