#include "../state/State.h"
#include "engine.h"
#include "Order.h"
#include "Move.h"
#include <iostream>
using namespace std;
using namespace state;
using namespace engine;

Move::Move(state::Animal* targetAnimal, state::Coord& targetCoord): targetAnimal(targetAnimal),targetCoord(targetCoord){

}


void engine::Move::execute(engine::Engine* engine)
{
  std::vector<std::pair<state::Coord,engine::ActionID>> noHighlights; //clean all the highlights with one NONE highlight
  noHighlights.push_back(make_pair(Coord {0,0},ActionID{NONE}));
  std::vector<std::pair<state::Coord,engine::ActionID>>& refNoHighlights = noHighlights;
  engine->getState().setHighlights(refNoHighlights);

  std::vector<std::pair<state::Coord,engine::ActionID>> authorisedActions = engine->authorisedActions(engine->getState(),this->targetAnimal->getCoord());
  cout<<"Tour numéro : " << engine->getState().getTurn() << endl;
  cout<<"Anciennes coord           :" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
  cout<<"Nouvelles coord demandées :" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;

  for (int i =0 ;i<=3 ;i++){
    if (authorisedActions[i].first == this->targetCoord){
      switch(authorisedActions[i].second)
      {
        case SHIFT :
          this->targetAnimal->setCoord(this->targetCoord);
          break;
        case ATTACK :
          cout<<"Animal adverse DEAD" <<endl;
          engine->getState().getSelection(this->targetCoord).first->setStatus(DEAD);
          this->targetAnimal->setCoord(this->targetCoord);
          break;
        case JUMP :
          this->targetAnimal->setCoord(this->targetCoord);
          break;
        case SHIFT_TRAPPED :
          cout<<"Animal TRAPPED" <<endl;
          this->targetAnimal->setCoord(this->targetCoord);
          break;
        case SHIFT_VICTORY :
          cout<<"Animal VICTORY" <<endl;
          this->targetAnimal->setCoord(this->targetCoord);

          if(engine->getState().getSelection(this->targetAnimal->getCoord()).second == 0){
            engine->getState().setWinner(engine->getState().getPlayer1());
            cout<<"Victoire du Joueur1 "<< engine->getState().getPlayer1().getName() << "BRAVO !!!";
          } else{
            engine->getState().setWinner(engine->getState().getPlayer2());
            cout<<"Victoire du Joueur2 "<< engine->getState().getPlayer2().getName() << "BRAVO !!!";
          }
          engine->getState().setGameover(1);
          break;
      }
    }
  }

  if(engine->getState().getPlaying() == 0){
    engine->getState().setPlaying(1);
  } else if (engine->getState().getPlaying() == 1){
    engine->getState().setPlaying(0);
  }
  engine->getState().setTurn(engine->getState().getTurn()+1);
  cout<<"Passage au tour numéro : " << engine->getState().getTurn() << endl;
  cout<<"C'est au joueur " << engine->getState().getPlaying() << " de jouer"<< endl;
}
