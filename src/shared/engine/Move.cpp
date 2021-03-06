#include "../state/State.h"
#include "engine.h"
#include "Order.h"
#include "Move.h"
#include <json/json.h>
#include <iostream>
using namespace std;
using namespace state;
using namespace engine;

Move::Move(state::Animal* targetAnimal, state::Coord targetCoord, bool player): targetAnimal(targetAnimal),targetCoord(targetCoord){
  this->ID = MOVE;
  this->player = player;
}

Move::Move(){
  new (this) Move(NULL, Coord(0,0), 0);
}

/*Move::Move(const engine::Move& move){
  this->ID = move.ID;
  this->player = move.player;
  this->targetAnimal = move.targetAnimal;
  targetCoord = new Coord(move.targetCoord);
}*/

Json::Value Move::serialize (){
  Json::Value newCommand;
	/*newCommand["animal"] = (int)targetAnimal;*/
  newCommand["player"] = player;
  newCommand["orderID"] = getOrderID();
  newCommand["animalID"] = targetAnimal->getID();
  newCommand["xDestination"] = targetCoord.getX();
  newCommand["yDestination"] = targetCoord.getY();
	return newCommand;
}

void engine::Move::execute(engine::Engine* engine)
{
  State& state = engine->getState();
  engine->addState(state);
  std::vector<std::pair<state::Coord,engine::ActionID>> noHighlights; //clean all the highlights with one NONE highlight
  noHighlights.push_back(make_pair(Coord {0,0},ActionID{NONE}));
  std::vector<std::pair<state::Coord,engine::ActionID>>& refNoHighlights = noHighlights;
  state.setHighlights(refNoHighlights);

  std::vector<std::pair<state::Coord,engine::ActionID>> authorisedActions = engine->authorisedActions(state,this->targetAnimal->getCoord());
  cout << "\n\033[1;37m Engine\033[0m" << endl;
  cout<<"Anciennes coord           :" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
  cout<<"Nouvelles coord demandées :" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;

  bool actionValide = false;
  for (int i =0 ;i<=3 ;i++){
    if (authorisedActions[i].first == this->targetCoord){
      switch(authorisedActions[i].second)
      {
        case NONE :
          break;
        case SHIFT :
          actionValide = true;
          this->targetAnimal->setCoord(this->targetCoord);
          break;
        case ATTACK :
          actionValide = true;
          cout<<"Animal adverse DEAD" <<endl;
          state.getSelection(this->targetCoord).first->setStatus(DEAD);
          this->targetAnimal->setCoord(this->targetCoord);
          break;
        case JUMP :
          actionValide = true;
          this->targetAnimal->setCoord(this->targetCoord);
          break;
        case SHIFT_TRAPPED :
          actionValide = true;
          cout<<"Animal TRAPPED" <<endl;
          this->targetAnimal->setCoord(this->targetCoord);
          break;
        case SHIFT_VICTORY :
          actionValide = true;
          cout<<"Animal VICTORY" <<endl;
          this->targetAnimal->setCoord(this->targetCoord);
          if(state.getSelection(this->targetAnimal->getCoord()).second == 0){
            state.setWinner(state.getPlayer1());
            cout<<"Victoire du Joueur1 "<< state.getPlayer1().getName() << " BRAVO !!!";
          } else{
            state.setWinner(state.getPlayer2());
            cout<<"Victoire du Joueur2 "<< state.getPlayer2().getName() << " BRAVO !!!";
          }
          state.setGameover(1);
          break;
      }
    }
  }

  if(actionValide == true){
    if(state.getPlaying() == 0){
      state.setPlaying(1);
    } else if (state.getPlaying() == 1){
      state.setPlaying(0);
    }
    state.setTurn(state.getTurn()+1);
    cout<<"Action effectuée par l'engine !"<<endl;
    cout<<"Passage au tour numéro : " << state.getTurn() << endl;
    cout<<"C'est au joueur " << state.getPlaying()+1 << " de jouer"<< endl;
  } else {
    cout<<"action non valide, c'est encore le tour numero " << state.getTurn() << endl;
  }
  cout << "\n\033[1;37m Render\033[0m" << endl;

  StateEvent allChangedEvent(ALL_CHANGED);
  StateEvent& refAllChangedEvent = allChangedEvent;
  state.notifyObservers(refAllChangedEvent);
}
