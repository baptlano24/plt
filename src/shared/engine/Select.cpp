#include "../state/State.h"
#include "Engine.h"
#include "Order.h"
#include "Select.h"
#include <iostream>
using namespace std;
using namespace state;
using namespace engine;


Select::Select(Animal* targetAnimal, Coord& targetCoord):targetAnimal(targetAnimal), targetCoord(targetCoord){
    this->ID = SELECT;
    this->player = 0;
}

void Select::execute(Engine* engine)
{
  State& state = engine->getState();
  cout<<"Début du tour numéro : " << engine->getState().getTurn() << endl;
  cout<<"Case SELECT : (" << this->targetCoord.getX()<< "," << this->targetCoord.getY() << ")"<< endl;

  cout<<"Les coups possibles sont :" << endl;
  std::vector<std::pair<state::Coord,engine::ActionID>> authorisedActions = engine->authorisedActions(engine->getState(),this->targetAnimal->getCoord());
  std::vector<std::pair<state::Coord,engine::ActionID>> newHighlights = authorisedActions;
  newHighlights.push_back(make_pair(this->targetCoord, ActionID {NONE}));

  std::vector<std::pair<state::Coord,engine::ActionID>>& refNewHighlights = newHighlights;
  engine->getState().setHighlights(refNewHighlights);

  for (int i =0 ;i<=3 ;i++) {
    cout<<"  Case voisine: (" << authorisedActions[i].first.getX()<< "," << authorisedActions[i].first.getY() << ") avec action " << authorisedActions[i].second << endl;
  }
  StateEvent highlightsChangedEvent(HIGHLIGHTS_CHANGED);
  StateEvent& refHighlightsChangedEvent = highlightsChangedEvent;
  state.notifyObservers(refHighlightsChangedEvent, state);
}
