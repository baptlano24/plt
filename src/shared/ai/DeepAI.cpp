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
#include <thread>

using namespace std;
using namespace state;
using namespace engine;
using namespace ai;

DeepAI::DeepAI(int color, engine::Engine* engine, int depth_in){
  this->color = color;
  this->map = &engine->getState().getGrid();
  this->ready = false;
  this->loading = false;
  if(depth_in>=1 && depth_in<=5){
    this->depth = depth_in;
  } else {
    this->depth = 1;
  }
}

void DeepAI::play(engine::Engine* engine) {
  if(this->loading == true){
    cout << "  >> DeepAI : I'm currently working on a new move, please wait." << endl;
  } else {
    cout << "  >> DeppAI : I start to calculate next move" << endl;
    this->ready = false;
    this->loading = true;

    Move moveIA = calculateNextMove(engine);
    this->nextMove = moveIA;

    this->loading = false;
    this->ready = true;
  }
}

engine::Move DeepAI::calculateNextMove(engine::Engine* engine){
  State& state = engine->getState();

  cout << "\033[1;35m   DeepAI building the tree... \033[0m" << endl;
  Vertex parentVertex(state);
  double max = std::numeric_limits<double>::max();
  double min = -max;
  Action bestAction = minmaxAlphabeta(&parentVertex, this->depth, true, this->depth, min, max);
  Animal* selectedAnimal = state.getSelection(bestAction.getAnimal().getCoord()).first;
  Coord selectedCoord = bestAction.getCoord();
  cout << "\033[1;33m  DeepIA (niveau " << this->depth << ") : I decide to move my " << selectedAnimal->getName() << " from (" << selectedAnimal->getCoord().getX() << "," << selectedAnimal->getCoord().getY() << ") to (" << selectedCoord.getX() << "," << selectedCoord.getY() << ") for a score " << bestAction.getScore() << "\033[0m"<< endl;

  engine::Move moveIA(selectedAnimal, selectedCoord, this->color);
  return moveIA;
}

engine::Move DeepAI::getNextMove(){
  this->ready = false;
  return this->nextMove;
}

Action DeepAI::minmax (Vertex* vertex, int depth, bool maximizing, int totalDepth){

  if (depth == 0){
    calculateVertexScore(vertex, maximizing);
    return vertex->getAction();
  } else if (depth == totalDepth){
    std::vector<Action> listActions = enumerateActions(vertex);
    double max = std::numeric_limits<double>::max();
    Action action_vertex = vertex->getAction();
    action_vertex.setScore(-max);
    for(auto action : listActions){
      Vertex child = Vertex(vertex, action);
      Action action_minmax = DeepAI::minmax(&child,depth-1,false,totalDepth);
      cout << "\033[1;32m   -team "<< vertex->getPlaying() <<" with " << action_minmax.getAnimal().getName() << " (" << action_minmax.getAnimal().getCoord().getX() << "," << action_minmax.getAnimal().getCoord().getY() << ") go in (" << action_minmax.getCoord().getX() << "," << action_minmax.getCoord().getY() << ") to ID "<< action_minmax.getId() <<" with score "<< action_minmax.getScore() << "\033[0m" << endl;
      action_vertex = DeepAI::max(action_vertex, action_minmax);
    }
    return action_vertex;
  } else {
    std::vector<Action> listActions = enumerateActions(vertex);
    double max = std::numeric_limits<double>::max();
    Action action_vertex = vertex->getAction();
    if(maximizing){
      action_vertex.setScore(-max);
      for(auto action : listActions){
        Vertex child = Vertex(vertex, action);
        Action action_minmax = DeepAI::minmax(&child,depth-1,false,totalDepth);
        //cout << "\033[1;35m       -team "<< vertex->getPlaying() <<" with " << action_minmax.getAnimal().getName() << " (" << action_minmax.getAnimal().getCoord().getX() << "," << action_minmax.getAnimal().getCoord().getY() << ") go in (" << action_minmax.getCoord().getX() << "," << action_minmax.getCoord().getY() << ") to ID "<< action_minmax.getId() <<" with score "<< action_minmax.getScore() << "\033[0m" << endl;
        action_vertex.setScore(DeepAI::max(action_vertex, action_minmax).getScore());
      }
      return action_vertex;
    }else{
      action_vertex.setScore(max);
      for(auto action : listActions){
        Vertex child = Vertex(vertex, action);
        Action action_minmax = DeepAI::minmax(&child,depth-1,true,totalDepth);
        //cout << "\033[1;34m     -team "<< vertex->getPlaying() <<" with " << action_minmax.getAnimal().getName() << " (" << action_minmax.getAnimal().getCoord().getX() << "," << action_minmax.getAnimal().getCoord().getY() << ") go in (" << action_minmax.getCoord().getX() << "," << action_minmax.getCoord().getY() << ") to ID "<< action_minmax.getId() <<" with score "<< action_minmax.getScore() << "\033[0m" << endl;
        action_vertex.setScore(DeepAI::min(action_vertex, action_minmax).getScore());
      }
      return action_vertex;
    }
  }

}

Action DeepAI::minmaxAlphabeta (Vertex* vertex, int depth, bool maximizing, int totalDepth, double alpha, double beta){

  if (depth == 0){
    //cout << endl <<"    |--Profondeur " << depth << " avec ab["<< alpha <<" ,"<< beta <<"]"<< endl;
    calculateVertexScore(vertex, maximizing);
    //cout << "     return score " << vertex->getAction().getScore() << endl;
    return vertex->getAction();
  } else if (depth == totalDepth){
    //cout << endl <<"  |--Profondeur " << depth << " avec ab["<< alpha <<" ,"<< beta <<"]"<< endl;
    //cout << "ab1" << endl;
    std::vector<Action> listActions = enumerateActions(vertex);
    double max = std::numeric_limits<double>::max();
    Action action_vertex = vertex->getAction();
    action_vertex.setScore(-max);
    for(auto action : listActions){
        Vertex child = Vertex(vertex, action);
        Action action_minmax = DeepAI::minmaxAlphabeta(&child,depth-1,false,totalDepth, alpha, beta);
        cout << "\033[1;32m   -team "<< vertex->getPlaying() <<" with " << action_minmax.getAnimal().getName() << " (" << action_minmax.getAnimal().getCoord().getX() << "," << action_minmax.getAnimal().getCoord().getY() << ") go in (" << action_minmax.getCoord().getX() << "," << action_minmax.getCoord().getY() << ") to ID "<< action_minmax.getId() <<" with score "<< action_minmax.getScore() << "\033[0m" << endl;
        action_vertex = DeepAI::max(action_vertex, action_minmax);
    }
    //cout << " return action_vertex (score+action) " << action_vertex.getScore() << endl;
    return action_vertex;
  } else {
    //cout << endl <<"|--Profondeur " << depth << " avec ab["<< alpha <<" ,"<< beta <<"]"<< endl;
    std::vector<Action> listActions = enumerateActions(vertex);
    double max = std::numeric_limits<double>::max();
    Action action_vertex = vertex->getAction();
    if(maximizing){
      //cout << "ab6 maximise" << endl;
      action_vertex.setScore(-max);
      for(auto action : listActions){
          Vertex child = Vertex(vertex, action);
          Action action_minmax = DeepAI::minmaxAlphabeta(&child,depth-1,false,totalDepth, alpha, beta);
          //cout << "   action_minmax :" << action_minmax.getScore() << endl;
          double max_score = DeepAI::max(action_vertex, action_minmax).getScore();
          //cout << "   action_vertex    :" << action_vertex.getScore() << endl;
          //cout << "  maxscore entre vertex et minmax:" << max_score << endl;
          action_vertex.setScore(max_score);
            if(max_score > beta){
              //cout << "ELAGAGE car le score max " << max_score << " est plus grand que beta " << beta << endl;
              return action_vertex;
            }
          //cout << "Modification de alpha " << beta << " en " <<std::max(alpha, max_score) << endl;
          alpha = std::max(alpha, max_score);
        }
    } else {
      //cout << "ab6 minimise" << endl;
      action_vertex.setScore(max);
      for(auto action : listActions){
          Vertex child = Vertex(vertex, action);
          Action action_minmax = DeepAI::minmaxAlphabeta(&child,depth-1,true,totalDepth, alpha, beta);
          //cout << "   action_minmax :" << action_minmax.getScore() << endl;
          double min_score = DeepAI::min(action_vertex, action_minmax).getScore();
          //cout << "   action_vertex    :" << action_vertex.getScore() << endl;
          //cout << "  minscore entre vertex et minmax:" << min_score << endl;
          action_vertex.setScore(min_score);
          if (alpha > min_score){
              //cout << "ab7" << endl;
              //cout << "ELAGAGE" << endl;
              //cout << "ELAGAGE car le score min " << min_score << " est plus petit que alpha " << alpha << endl;
              return action_vertex;
          }
          //cout << "Modification de beta " << beta << " en " << std::min(beta,min_score) << endl;
          beta = std::min(beta,min_score);
      }
      //cout << "ab8" << endl;
    }
    //cout << " return action_vertex (score) " << action_vertex.getScore() << endl;
    return action_vertex;
  }
}

double DeepAI::calculateAnimalScore(Vertex* vertex, Animal* myAnimal, bool maximizing){
  std::vector<state::Animal>* hisAnimals;
  Coord myObjective;
  Coord hisObjective;
  if(maximizing){
    hisAnimals = vertex->getMyAnimals();
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
  } else {
    hisAnimals = vertex->getMyAnimals();
    if (vertex->getPlaying()==0){
      myObjective.setX(5);
      myObjective.setY(0);
      hisObjective.setX(6);
      hisObjective.setY(12);
    } else {
      myObjective.setX(6);
      myObjective.setY(12);
      hisObjective.setX(5);
      hisObjective.setY(0);
    }
  }
  /****** PARAMETERS ******/
  Coord myCoord = myAnimal->getCoord();
  Coord hisCoord;

  int distancePrey;
  int distancePredator;
  int distanceObjectif = getDistance(myObjective, myCoord);
  int distanceEnnemyWin;
  AnimalID myAnimalID = myAnimal->getID();
  AnimalID hisAnimalID;

  double preyScore = 0;
  double predatorScore = 0;
  double objectifScore = 1000/(distanceObjectif+0.1);
  /****** END PARAMETERS ******/

  for (auto& hisAnimal : *hisAnimals){
    hisAnimalID = hisAnimal.getID();
    hisCoord = hisAnimal.getCoord();
    distanceEnnemyWin = getDistance(hisObjective, hisCoord);
    if( hisAnimalID <= myAnimalID || (hisAnimalID==ELEPHANT && myAnimalID==RAT) || this->map->at(hisCoord.getX())[hisCoord.getY()].getID() == TRAPJ2 ){
      distancePrey = getDistance(myCoord, hisCoord);
      preyScore += exp(-distancePrey/5+2.5)*hisAnimal.getID()/(distanceEnnemyWin+0.1);
    } else if( hisAnimalID >= myAnimalID || (hisAnimal.getID()==RAT && myAnimalID==ELEPHANT) || this->map->at(myCoord.getX())[myCoord.getY()].getID() == TRAPJ1 ){
      distancePredator = getDistance(myCoord, hisCoord);
      predatorScore += (-200)*exp(-distancePredator/2);
    }
  }

  double totalScore = preyScore + objectifScore + predatorScore + rand() % 10;
  return totalScore;
}

void DeepAI::calculateVertexScore(Vertex* vertex, bool maximizing){
  double score = 0;
  std::vector<state::Animal>* myAnimals;;
  std::vector<state::Animal>* hisAnimals;

  if(!maximizing){
    myAnimals = vertex->getHisAnimals();
    hisAnimals = vertex->getMyAnimals();
  } else {
    myAnimals = vertex->getMyAnimals();
    hisAnimals = vertex->getHisAnimals();
  }
  for (auto& hisAnimal : *hisAnimals){
    score -= 100*hisAnimal.getID();
  }
  for (auto& myAnimal : *myAnimals){
    score += 100*myAnimal.getID();
    score += calculateAnimalScore(vertex, &myAnimal, maximizing);
  }

  vertex->setActionScore(score);
}

std::vector<Action> DeepAI:: enumerateActions (Vertex* vertex){
  //cout << "  enumerateActions(vertex team " << vertex->getPlaying() << ")"<< endl;
  /*cout << "  Ally team " << vertex->getPlaying() << " contains   : ";
  for(auto& myAnimal : *vertex->getMyAnimals()){
    cout << myAnimal.getName() << ", ";
  }
  cout << endl;
  cout << "  Ennemy team contains : ";
  for(auto& hisAnimal : *vertex->getHisAnimals()){
    cout << hisAnimal.getName() << ", ";
  }*/
  std::vector<Action> listAction;
  std::array<std::array<state::Square,13>,12>* map = getMap();
  std::array<std::array<state::Square,13>,12> map1 = *map;
  int playing = vertex->getPlaying();

  for(auto& myAnimal : *vertex->getMyAnimals()){
    //cout << "\033[1;31m        animal team "<< vertex->getPlaying() <<" coord " << myAnimal.getName() << " (" << myAnimal.getCoord().getX() << "," << myAnimal.getCoord().getY() << ")\033[0m" << endl;
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
  if(action1.getScore()<action2.getScore()){
    return action1;
  }
  else{
    return action2;
  }
}

std::array<std::array<state::Square,13>,12>* DeepAI::getMap(){
   return this->map;
}

bool DeepAI::isReady(){
  return this->ready;
}

bool DeepAI::isLoading(){
  return this->loading;
}
