#include "../state/State.h"
#include "DeepAI.h"
#include "Vertex.h"
#include "state.h"
#include "engine.h"
#include "Action.h"
#include <unistd.h>
#include <iostream>
#include <limits>
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

  State& state = engine->getState();

  StateEvent animalChangedEvent(ANIMALS_CHANGED);
  StateEvent& refAnimalChangedEvent = animalChangedEvent;
  StateEvent highlightsChangedEvent(HIGHLIGHTS_CHANGED);
  StateEvent& refHighlightsChangedEvent = highlightsChangedEvent;
  StateEvent infosChangedEvent(INFOS_CHANGED);
  StateEvent& refInfosChangedEvent = infosChangedEvent;

  cout << "\033[1;35m   DeepAI building the tree... \033[0m" << endl;
  Vertex parentVertex(state);
  int depth = 3;

  Action bestAction = minmax(&parentVertex, depth, true, depth);
  Animal* selectedAnimal = state.getSelection(bestAction.getAnimal().getCoord()).first;
  Coord selectedCoord = bestAction.getCoord();

  cout << "\033[1;33m  DeepIA : I decide to move my " << selectedAnimal->getName() << " in (" << selectedCoord.getX() << "," << selectedCoord.getY() << ") for a score " << bestAction.getScore() << "\033[0m"<< endl;
  Move moveDeepIA(selectedAnimal,selectedCoord);
  moveDeepIA.execute(engine);

  state.notifyObservers(refAnimalChangedEvent, state);
  state.notifyObservers(refHighlightsChangedEvent, state);
  state.notifyObservers(refInfosChangedEvent, state);
}

Action DeepAI::minmax (Vertex* vertex, int depth, bool maximizing, int totalDepth){
  std::vector<Action> listActions = this->enumerateActions(vertex);
  double max = std::numeric_limits<double>::max();
  Action action_vertex = vertex->getAction();

  //cout << " >> DEPTH = " << depth << endl;
  if (depth == 0){
    calculateVertexScore(vertex);
    return vertex->getAction();
  } else if (depth == totalDepth){
    action_vertex.setScore(-max);
    for(auto action : listActions){
      Vertex child = Vertex(vertex, action);
      Action action_minmax = DeepAI::minmax(&child,depth-1,false,totalDepth);
      action_vertex = DeepAI::max(action_vertex, action_minmax);
    }
    return action_vertex;
  } else {
    if(maximizing){
      action_vertex.setScore(-max);
      for(auto action : listActions){
        Vertex child = Vertex(vertex, action);
        Action action_minmax = DeepAI::minmax(&child,depth-1,false,totalDepth);
        action_vertex.setScore(DeepAI::max(action_vertex, action_minmax).getScore());
      }
      return action_vertex;
    }else{
      action_vertex.setScore(max);
      for(auto action : listActions){
        Vertex child = Vertex(vertex, action);
        Action action_minmax = DeepAI::minmax(&child,depth-1,true,totalDepth);
        action_vertex.setScore(DeepAI::min(action_vertex, action_minmax).getScore());
      }
      if (depth == totalDepth-1){
        cout << "   Possible action team "<< vertex->getPlaying() <<" with " << action_vertex.getAnimal().getName() << " go in (" << action_vertex.getCoord().getX() << "," << action_vertex.getCoord().getY() << ") with score "<< action_vertex.getScore() << endl;
      }
      return action_vertex;
    }
  }
}

double DeepAI::calculateAnimalScore(Vertex* vertex, Animal* myAnimal){
  vector<Animal>& hisAnimals = *vertex->getHisAnimals();
  /****** PARAMETERS ******/
  Coord myObjective;
  Coord hisObjective;

  Coord myCoord = myAnimal->getCoord();
  Coord hisCoord;

  if (vertex->getPlaying()==0){
    myObjective.setX(6);
    myObjective.setY(12);
    hisObjective.setX(5);
    hisObjective.setY(0);
  } else {
    myObjective.setX(5);
    myObjective.setY(0);
    hisObjective.setX(6);
    hisObjective.setY(12);
  }

  int distancePrey;
  int distancePredator;
  int distanceObjectif = getDistance(myObjective, myCoord);
  int distanceEnnemyWin;
  AnimalID myAnimalID = myAnimal->getID();
  AnimalID hisAnimalID;

  double preyScore = 0;
  double predatorScore = 0;
  double objectifScore = exp(-distanceObjectif/6+4.9);
  /****** END PARAMETERS ******/

  for (auto& hisAnimal : hisAnimals){
    hisAnimalID = hisAnimal.getID();
    hisCoord = hisAnimal.getCoord();
    distanceEnnemyWin = getDistance(hisObjective, hisCoord);
    if( hisAnimalID <= myAnimalID || (hisAnimalID==ELEPHANT && myAnimalID==RAT) || this->map->at(hisCoord.getX())[hisCoord.getY()].getID() == TRAPJ2 ){
      distancePrey = getDistance(myCoord, hisCoord);
      preyScore += exp(-distancePrey/6+7.5)/distanceEnnemyWin;
    } else if( hisAnimalID >= myAnimalID || (hisAnimal.getID()==RAT && myAnimalID==ELEPHANT) || this->map->at(myCoord.getX())[myCoord.getY()].getID() == TRAPJ1 ){
      distancePredator = getDistance(myCoord, hisCoord);
      predatorScore += (-200)*exp(-distancePredator/2);
    }
  }

  double totalScore = preyScore + predatorScore + objectifScore;
  return totalScore;
}

void DeepAI::calculateVertexScore(Vertex* vertex){
  int nombreActions = (int)enumerateActions(vertex).size();
  double score = 0;
  for (auto& myAnimal : *vertex->getMyAnimals()){
    //score += calculateAnimalScore(vertex, &myAnimal);
    score += 100;
  }
  score += (8-(int)vertex->getHisAnimals()->size())*1000;
  score += nombreActions*10;
  vertex->setActionScore(score);
}

std::vector<Action> DeepAI:: enumerateActions (Vertex* vertex){
  std::vector<Action> listAction;
  std::array<std::array<state::Square,13>,12>* map = getMap();
  std::array<std::array<state::Square,13>,12> map1 = *map;
  int playing = vertex->getPlaying();

  for(auto& myAnimal : *vertex->getMyAnimals()){
    std::vector<state::Coord> listCoord;

    Coord current_square = myAnimal.getCoord();
    int csX = current_square.getX();
    int csY = current_square.getY();
    Coord right_square (csX+1,csY);
    Coord left_square  (csX-1,csY);
    Coord front_square (csX,csY-1);
    Coord behind_square(csX,csY+1);

    listCoord.push_back(right_square);
    listCoord.push_back(left_square);
    listCoord.push_back(behind_square);
    listCoord.push_back(front_square);
    std::pair<Animal*,int> selectionList;
    SquareID squareId_list;

    if (myAnimal.getID() == ELEPHANT || myAnimal.getID() ==  CAT || myAnimal.getID() == DOG || myAnimal.getID() == WOLF){
        //cout << "NORMAL!" << endl;
        for (auto& coord : listCoord) {
          if (coord.getX()<=11 && coord.getX()>=0 && coord.getY()<= 12 && coord.getY()>=0){
            selectionList = getSelection(vertex,coord);
            squareId_list = map1[coord.getX()][coord.getY()].getID();
            if(squareId_list!= WATER){
              //cout << "NOWATER!" << endl;
              if(selectionList.first && selectionList.first->getStatus() != DEAD ){
                //cout << "SOMEONE!" << endl;
                if(selectionList.second != playing){
                  //cout << "ENNEMY" << endl;
                  if((myAnimal.getID()>=selectionList.first->getID())||((squareId_list== TRAPJ1 && selectionList.second == 1 )||(squareId_list== TRAPJ2 && selectionList.second == 0))){
                      //cout << "A L'ATTAQUE!" << endl;
                      listAction.push_back(Action(0,myAnimal,coord,ATTACK));
                    }
                }
              } else {
                if((squareId_list== TRAPJ1 && playing == 0 )||(squareId_list== TRAPJ2 && playing == 1)){
                  //cout <<"TRAP ALLIE" << endl;
                  listAction.push_back(Action(0,myAnimal,coord,SHIFT));
                }
                else if((squareId_list== TRAPJ1 && playing == 1 )||(squareId_list== TRAPJ2 && playing == 0)){
                  //cout <<"TRAPPED" << endl;
                  listAction.push_back(Action(0,myAnimal,coord,SHIFT_TRAPPED));
                }
                else if((squareId_list== THRONEJ1 && playing == 1 )||(squareId_list== THRONEJ2 && playing == 0)){
                //cout <<  "VICTORY SOON" << endl;
                  listAction.push_back(Action(0,myAnimal,coord,SHIFT_VICTORY));
                }
                else if((squareId_list== THRONEJ1 && playing == 0 )||(squareId_list== THRONEJ2 && playing == 1)){
                //cout <<  "YOU ARE NOT THE KING! GO OUT!" << endl;
                  //do nothing
                }
                else {
                //cout <<  "MOVE" << endl;
                  listAction.push_back(Action(0,myAnimal,coord,SHIFT));
                }

              }
            }
          }
        } // end for

    } else if (myAnimal.getID() == RAT) {

          for (auto& coord : listCoord) {
            if (coord.getX()<=11 && coord.getX()>=0 && coord.getY()<= 12 && coord.getY()>=0){
            selectionList = getSelection(vertex,coord);
            squareId_list = map1[coord.getX()][coord.getY()].getID();
              if(selectionList.first){
                  //cout << "SOMEONE!" << endl;
                if(selectionList.second == playing){
                  //cout << "COPAIN!" << endl;
                  //do nothing
                } else if(squareId_list!= WATER){
                    if(selectionList.first->getID() == ELEPHANT || selectionList.first->getID() == RAT){
                      //cout << "A L'ATTAQUE!" << endl;
                      listAction.push_back(Action(0,myAnimal,coord,ATTACK));
                    }
                    else if((selectionList.second != playing)
                         && ((squareId_list== TRAPJ1 && playing == 0) || (squareId_list== TRAPJ2 && playing == 1)) ){
                      //cout << " PIEGE ET A L'ATTAQUE!" << endl;
                      listAction.push_back(Action(0,myAnimal,coord,ATTACK));
                    }
                } else {
                  if (squareId_list== WATER) {
                    //cout << "ATTACK" << endl;
                    listAction.push_back(Action(0,myAnimal,coord,ATTACK));
                  }
                }
              } else {
                if((squareId_list== TRAPJ1 && playing == 1 )||(squareId_list== TRAPJ2 && playing == 0)){
                  //cout <<"TRAPPED" << endl;
                  listAction.push_back(Action(0,myAnimal,coord,SHIFT_TRAPPED));
                }
                else if((squareId_list== THRONEJ1 && playing == 1 )||(squareId_list== THRONEJ2 && playing == 0)){
                  //cout <<  "VICTORY SOON" << endl;
                  listAction.push_back(Action(0,myAnimal,coord,SHIFT_VICTORY));
                }
                else if((squareId_list== THRONEJ1 && playing == 0 )||(squareId_list== THRONEJ2 && playing == 1)){
                  //cout <<  "YOU ARE NOT THE KING! GO OUT!" << endl;
                  //do nothing
                }
                else{
                  //cout <<  "MOVE" << endl;
                  listAction.push_back(Action(0,myAnimal,coord,SHIFT));
                }
              }
            }
          } //end for
    } else if(myAnimal.getID() == TIGER || myAnimal.getID() == LEOPARD || myAnimal.getID() == LION) {
        int j = -1;
        for (auto& coord : listCoord) {
          j++;
          if (coord.getX()<=11 && coord.getX()>=0 && coord.getY()<= 12 && coord.getY()>=0){
          selectionList = getSelection(vertex,coord);
          squareId_list = map1[coord.getX()][coord.getY()].getID();
              if(squareId_list!= WATER){
                //cout << "NOWATER!" << endl;
                if(selectionList.first){
                  //cout << "SOMEONE!" << endl;
                  if(selectionList.second == playing){
                    //cout << "COPAIN!" << endl;
                    //do nothing
                  }
                  else{
                    if((myAnimal.getID()>=selectionList.first->getID())||((squareId_list== TRAPJ1 && selectionList.second == 1 )||(squareId_list== TRAPJ2 && selectionList.second == 0))){
                        //cout << "A L'ATTAQUE!" << endl;
                        listAction.push_back(Action(0,myAnimal,coord,ATTACK));
                      }
                  }

                }else{
                  if((squareId_list== TRAPJ1 && playing == 0 )||(squareId_list== TRAPJ2 && playing == 1)){
                    //cout <<"TRAP ALLIE" << endl;
                    listAction.push_back(Action(0,myAnimal,coord,SHIFT));
                  }
                  else if((squareId_list== TRAPJ1 && playing == 1 )||(squareId_list== TRAPJ2 && playing == 0)){
                    //cout <<"TRAPPED" << endl;
                    listAction.push_back(Action(0,myAnimal,coord,SHIFT_TRAPPED));
                  }
                  else if((squareId_list== THRONEJ1 && playing == 1 )||(squareId_list== THRONEJ2 && playing == 0)){
                  //cout <<  "VICTORY SOON" << endl;
                    listAction.push_back(Action(0,myAnimal,coord,SHIFT_VICTORY));
                  }
                  else if((squareId_list== THRONEJ1 && playing == 0 )||(squareId_list== THRONEJ2 && playing == 1)){
                  //cout <<  "YOU ARE NOT THE KING! GO OUT!" << endl;
                    //do nothing
                  }
                  else{
                  //cout <<  "MOVE" << endl;
                    listAction.push_back(Action(0,myAnimal,coord,SHIFT));
                  }

                }
              }else{
                if(j == 0){
                  int compteur = 0;
                  for(int n = 0; n<3; n++){
                    if(getSelection(vertex,Coord(coord.getX()+n, coord.getY())).first==NULL){
                      compteur += 1;
                    if (compteur == 4){
                      //cout <<"CAN JUMP" << endl;
                      coord = Coord(coord.getX()+3, coord.getY());
                      listAction.push_back(Action(0,myAnimal,coord,JUMP));
                    }
                  }
                }

                //Jump
              } else if (j==1){
                int compteur = 0;
                for(int n = 0; n<3; n++){
                  if(getSelection(vertex,Coord(coord.getX()-n, coord.getY())).first==NULL){
                    compteur += 1;
                    if (compteur == 4){
                      //cout <<"CAN JUMP" << endl;
                      coord = Coord(coord.getX()-3, coord.getY());
                      listAction.push_back(Action(0,myAnimal,coord,JUMP));
                    }
                  }
                }
              } else if(j==2){
                int compteur = 0;
                for(int n = 0; n<3; n++){
                  if(getSelection(vertex,Coord(coord.getX(), coord.getY()+n)).first==NULL){
                    compteur += 1;
                    if (compteur == 4){
                      //cout <<"CAN JUMP" << endl;
                      coord = Coord(coord.getX(), coord.getY()+3);
                      listAction.push_back(Action(0,myAnimal,coord,JUMP));
                      compteur = 0;
                    }
                  }
                }
              } else{
                int compteur = 0;
                for(int n = 0; n<3; n++){
                  if(getSelection(vertex,Coord(coord.getX(), coord.getY()-n)).first==NULL){
                    compteur += 1;
                    if (compteur == 4){
                      //cout <<"CAN JUMP" << endl;
                      coord = Coord(coord.getX(), coord.getY()-3);
                      listAction.push_back(Action(0,myAnimal,coord,JUMP));
                    }
                  }
                }
              }
            }
          }
        }// end for
      }
    }
  return listAction;
}


int DeepAI::getDistance(Coord& coord1, Coord& coord2){
  int distance;
  distance = abs(coord2.getX()-coord1.getX())+abs(coord2.getY()-coord1.getY());
  return distance;
}

pair<Animal*, int> DeepAI::getSelection(Vertex* vertex, Coord coord)
{
  pair<Animal*, int> selection;
  selection.first = NULL;
  selection.second = -1;

  for (auto& myAnimal : *vertex->getMyAnimals()) {
    if (myAnimal.getCoord() == coord ) {
      selection.first = &myAnimal;
      if(vertex->getPlaying() == 0){
        selection.second = 0;
      } else {
        selection.second = 1;
      }
    }
  }
  for (auto& hisAnimal : *vertex->getHisAnimals()) {
    if (hisAnimal.getCoord() == coord ) {
      selection.first = &hisAnimal;
      if(vertex->getPlaying() == 0){
        selection.second = 1;
      } else {
        selection.second = 0;
      }
    }
  }
  return selection;
}

Action DeepAI::max(Action& action1,Action& action2){
  if(action1.getScore()>action2.getScore()){
    return action1;
  }
  else{
    return action2;
  }
}

Action DeepAI::min(Action& action1,Action& action2){
  if(action1.getScore()>action2.getScore()){
    return action2;
  }
  else{
    return action1;
  }
}

std::array<std::array<state::Square,13>,12>* DeepAI::getMap(){
   return this->map;
}
