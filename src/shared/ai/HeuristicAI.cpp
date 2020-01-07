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
    pair<Animal*, int> selectionIA = this->selectAnimal(engine);
    selectedAnimal = selectionIA.first;
    engine::Select selectIA(selectedAnimal, selectedAnimal->getCoord(), this->color);
    Order* orderIA = &selectIA;
    if(engine->getEnableRecord() == true){
      engine->addOrder(1,orderIA);
    }
    selectIA.execute(engine);
    //engine->update();
    engine->getState().notifyObservers(refHighlightsChangedEvent, engine->getState());
    animalSelectedIA = true;
  }
  if (animalSelectedIA == true) {
    cout << "-- Beginning of the IA Heuristic move --        Animal "<< selectedAnimal->getName() << endl;
    cout << "               [State score before : " << calculateScoreState(engine->getState(), this->color) << " ]" << endl;
    std::pair<state::Coord,engine::ActionID> action = this->selectAction(engine, selectedAnimal->getCoord());
    targetCoord.setX(action.first.getX());
    targetCoord.setY(action.first.getY());
    engine::Move moveIA(selectedAnimal, refTargetCoord, this->color);
    Order* ptr_move = &moveIA;
    if(engine->getEnableRecord() == true){
      engine->addOrder(2,ptr_move);
    }
    //engine->update();
    moveIA.execute(engine);
    cout << "               [State score after  : " << calculateScoreState(engine->getState(), this->color) << " ]" << endl;

    engine->getState().notifyObservers(refAnimalChangedEvent, engine->getState());
    engine->getState().notifyObservers(refHighlightsChangedEvent, engine->getState());
    engine->getState().notifyObservers(refInfosChangedEvent, engine->getState());
    animalSelectedIA = false;
    cout << "-- End of the IA move --" << endl;
  }
}

std::pair<state::Coord,engine::ActionID> HeuristicAI::selectAction(engine::Engine* engine, Coord& current_square){
  Coord objectifJ1(6,12);
  Coord objectifJ2(5,0);
  std::vector<std::pair<state::Coord,engine::ActionID>> authorisedActions = engine->authorisedActions(engine->getState(),current_square);
  pair<Animal*, int> selection = engine->getState().getSelection(current_square);

  double score;
  score = calculateScore(engine->getState(), selection.first, current_square, objectifJ1, objectifJ2);
  cout << "          -> score actuel de l'animal " << selection.first->getName() <<" : "<< score << " sur la case ("<< current_square.getX() << "," << current_square.getY() << ")" << endl;
  double scoreMax = -900000000000;
  pair<state::Coord,engine::ActionID> actionSelected;
  for(int i=0; i<4; ++i){
    if(authorisedActions[i].second != NONE){
      score = calculateScore(engine->getState(), selection.first, authorisedActions[i].first, objectifJ1, objectifJ2);
      if (scoreMax<score) {
        scoreMax = score;
        actionSelected = authorisedActions[i];
      }
      cout << "               => Score total "<< score <<" de la case ("<< authorisedActions[i].first.getX() << "," << authorisedActions[i].first.getY() << ")" << endl;
    }
  }
  return actionSelected;
}

pair<state::Animal*, int> HeuristicAI::selectAnimal(engine::Engine* engine)
{
  RandomAI randomAI(this->color);
  return randomAI.selectRandomAnimal(engine);

  /*vector<Animal>& animalsJ2 = engine->getState().getPlayer2().getAnimals();
  pair<Animal*, int> selection;

  if (this->color == 1){
    for (int i=0; i<8; ++i){
      if(animalsJ2[i].getID() == ELEPHANT){
        selection.first = &engine->getState().getPlayer2().getAnimals()[i];

      }
    }
  }
  selection.second = this->color;
  return selection;*/
}

double HeuristicAI::calculateScoreState(State& state, int color){
  double score = 0;
  Coord objectifJ1(6,12);
  Coord objectifJ2(5,0);

  if(color == 0){
    for (int i=0; i<8; ++i){
      score = score + calculateScore(state, &state.getPlayer1().getAnimals()[i], state.getPlayer1().getAnimals()[i].getCoord(), objectifJ1, objectifJ2);
    }
  } else {
    for (int i=0; i<8; ++i){
      score = score + calculateScore(state, &state.getPlayer2().getAnimals()[i], state.getPlayer2().getAnimals()[i].getCoord(), objectifJ1, objectifJ2);
    }
  }




  return score;
}


double HeuristicAI::calculateScore(State& state, Animal* selectedAnimal, Coord& coord, Coord& objectifJ1, Coord& objectifJ2){
  double preyScore = 0;
  double predatorScore = 0;
  double objectifScore = 0;

  vector<Animal>& animalsJ1 = state.getPlayer1().getAnimals();
  vector<Animal>& animalsJ2 = state.getPlayer2().getAnimals();

  int distancePrey;
  int distancePredator;
  int distanceObjectif;
  int distanceEnnemyWin;
  int counterPrey = 0;
  int counterPredator = 0;

  if (selectedAnimal){
    if(this->color == 0){
      for (int i=0; i<8; ++i){
        distanceEnnemyWin = getDistance(objectifJ2, animalsJ2[i].getCoord());
        if(animalsJ2[i].getStatus() != DEAD && (animalsJ2[i].getID() < selectedAnimal->getID()) ){
          distancePrey = getDistance(coord, animalsJ2[i].getCoord());
          preyScore += exp(-distancePrey/3+4.6);
        } else if(animalsJ2[i].getStatus() != DEAD && animalsJ2[i].getID() >= selectedAnimal->getID()){
          distancePredator = getDistance(coord, animalsJ2[i].getCoord());
          predatorScore += -exp(-distancePredator)*200;
        }
      }
      distanceObjectif = getDistance(coord, objectifJ1);
      objectifScore = exp(-distanceObjectif/2+4.8);
    } else if (this->color == 1){
      for (int i=0; i<8; ++i){
        distanceEnnemyWin = getDistance(objectifJ1, animalsJ1[i].getCoord());
        //cout << "   <-> distanceEnnemyWin " << distanceEnnemyWin << endl;
        if(animalsJ1[i].getStatus() != DEAD && (animalsJ1[i].getID() < selectedAnimal->getID()
                                              || (animalsJ1[i].getID()==ELEPHANT && selectedAnimal->getID()==RAT)
                                              || state.getSquare(animalsJ2[i].getCoord())->getID() == TRAPJ2) ){
          counterPrey ++;
          distancePrey = getDistance(coord, animalsJ1[i].getCoord());
          //cout << "   <-> distancePrey " << distancePrey << endl;
          //cout << "    ++preyScore  ++ " << exp(-distancePrey/3+6.4) << endl;
          //cout << "    ++preyScore/d++ " << exp(-distancePrey/3+6.4)/distanceEnnemyWin << endl;
          preyScore += exp(-distancePrey/6+7.5)/distanceEnnemyWin ;
        } else if(animalsJ1[i].getStatus() != DEAD && (animalsJ1[i].getID() >= selectedAnimal->getID()
                                                     || (animalsJ1[i].getID()==RAT && selectedAnimal->getID()==ELEPHANT)
                                                     || state.getSquare(selectedAnimal->getCoord())->getID() == TRAPJ1) ){
          counterPredator++;
          distancePredator = getDistance(coord, animalsJ1[i].getCoord());
          predatorScore += (-200)*exp(-distancePredator/2);
        }
      }
      preyScore /= counterPrey;
      predatorScore /= counterPredator;
      distanceObjectif = getDistance(coord, objectifJ2);
      objectifScore = exp(-distanceObjectif/6+4.9);
    }
  }
  //cout << "  ~ preyScore " << preyScore << endl;
  //cout << "  ~ predatorScore " << predatorScore << endl;
  //cout << "  ~ objectifScore " << objectifScore << endl;
  double totalScore = preyScore + predatorScore + objectifScore;

  return totalScore;
}

int HeuristicAI::getDistance(Coord& coord1, Coord& coord2){
  int distance;
  distance = abs(coord2.getX()-coord1.getX())+abs(coord2.getY()-coord1.getY());
  return distance;
}
