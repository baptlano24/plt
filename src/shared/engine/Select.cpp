#include "../state/State.h"
#include "Engine.h"
#include "Order.h"
#include "Select.h"
#include <iostream>
using namespace std;
using namespace state;
using namespace engine;


Select::Select(Animal* targetAnimal, Coord& targetCoord, bool player):targetAnimal(targetAnimal), targetCoord(targetCoord){
    this->ID = SELECT;
    this->player = player;
}
Json::Value Select::serialize (){
  Json::Value newCommand;
  cout << endl << "select" << endl;
  /*newCommand["animal"] = targetAnimal;*/
  /*newCommand["xDestination"] = (int)targetCoord.getX();
  /*newCommand["yDestination"] = (int)targetCoord.getY();*/

  return newCommand;
}

void Select::execute(Engine* engine)
{
  State& state = engine->getState();
  cout<<"Début du tour numéro : " << engine->getState().getTurn() << endl;
  cout<<"Case SELECT : (" << this->targetCoord.getX()<< "," << this->targetCoord.getY() << ")"<< endl;

  cout<<"Les coups possibles sont :" << endl;
  std::vector<std::pair<state::Coord,engine::ActionID>> authorisedActions = engine->authorisedActions(engine->getState(),this->targetAnimal->getCoord());
  std::vector<std::pair<state::Coord,engine::ActionID>> newHighlights = authorisedActions;
  std::vector<std::pair<state::Coord,engine::ActionID>>& refNewHighlights = newHighlights;
  engine->getState().setHighlights(refNewHighlights);

  for (int i =0 ;i<=3 ;i++) {
    cout<<"  Case voisine: (" << authorisedActions[i].first.getX()<< "," << authorisedActions[i].first.getY() << ") avec action " << authorisedActions[i].second << endl;
  }
  StateEvent highlightsChangedEvent(HIGHLIGHTS_CHANGED);
  StateEvent& refHighlightsChangedEvent = highlightsChangedEvent;
  state.notifyObservers(refHighlightsChangedEvent, state);
}
