#include "../state/State.h"
#include "RandomAI.h"
#include "engine.h"
#include <unistd.h>
#include <iostream>

using namespace std;
using namespace state;
using namespace engine;
using namespace ai;

RandomAI::RandomAI(){}

void RandomAI::play(engine::Engine* engine) {
  cout<<"randomIA play()"<<endl;

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
    pair<Animal*, int> selectionIA = this->getSelectionIA(engine);
    selectedAnimal = selectionIA.first;
    Select selectIA(selectedAnimal, selectedAnimal->getCoord());
    selectIA.execute(engine);
    engine->getState().notifyObservers(refHighlightsChangedEvent, engine->getState());
    animalSelectedIA = true;

  }
  if ((animalSelectedIA == true)) {
    cout << "-- Beginning of the IA move --" << endl;
    cout << "Animal selected id: " << selectedAnimal->getID() << endl;
    std::pair<state::Coord,engine::ActionID> randAction = this->randomAction(engine, selectedAnimal->getCoord());
    targetCoord.setX(randAction.first.getX());
    targetCoord.setY(randAction.first.getY());
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

std::pair<state::Coord,engine::ActionID> RandomAI::randomAction(engine::Engine* engine, Coord& current_square){
  std::pair<state::Coord,engine::ActionID> action;
  std::vector<std::pair<state::Coord,engine::ActionID>> authorisedActions = engine->authorisedActions(engine->getState(),current_square);
  int random = rand() % 4;
  while (authorisedActions[random].second == NONE){
     random = rand() % 4;
  }
  action = authorisedActions[random];
  return action;
}

pair<state::Animal*, int> RandomAI::getSelectionIA(engine::Engine* engine)
{
  pair<Animal*, int> selection;
  int random0_7 = rand() % 8;
  while(engine->getState().getPlayer1().getAnimals()[random0_7].getStatus() == DEAD){
     random0_7 = rand() % 8;
  }
  selection.first = &engine->getState().getPlayer1().getAnimals()[random0_7];
  selection.second = engine->getState().getPlayer1().getColor();
  return selection;
}
