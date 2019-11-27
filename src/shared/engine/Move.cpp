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
  std::vector<std::pair<state::Coord,engine::ActionID>> noHighlights; //clean all the highlights
  noHighlights.push_back(make_pair(Coord {0,0},ActionID{NONE}));
  std::vector<std::pair<state::Coord,engine::ActionID>>& refNoHighlights = noHighlights;
  engine->getState().setHighlights(refNoHighlights);

  std::vector<std::pair<state::Coord,engine::ActionID>> authorisedActions = engine->authorisedActions(engine->getState(),this->targetAnimal->getCoord());
  for (int i =0 ;i<=3 ;i++){
    if (authorisedActions[i].first == this->targetCoord){

      if (authorisedActions[i].second == SHIFT)//Higlight = 1 pour moove
      {
        cout<<"anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
        this->targetAnimal->setCoord(this->targetCoord);
        engine->getState().setTurn(engine->getState().getTurn()+1);
        cout<<"nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
      }

      if (authorisedActions[i].second == ATTACK )//Higlight = 2 pour attack
      {
        engine->getState().getSelection(this->targetCoord).first->setStatus(DEAD);
        cout<<"AnimalAdverseDEAD" <<endl;
        cout<<"anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
        this->targetAnimal->setCoord(this->targetCoord);
        engine->getState().setTurn(engine->getState().getTurn()+1);
        cout<<"nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
      }

      if (authorisedActions[i].second == JUMP)//Higlight = 3 pour moove
      {
        cout<<"anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
        this->targetAnimal->setCoord(this->targetCoord);
        engine->getState().setTurn(engine->getState().getTurn()+1);
        cout<<"nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
      }

      if (authorisedActions[i].second == SHIFT_TRAPPED)//Higlight = 4 pour moove
      {

        cout<<"Animal TRAPPED" <<endl;
        cout<<"anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
        this->targetAnimal->setCoord(this->targetCoord);
        engine->getState().setTurn(engine->getState().getTurn()+1);
        cout<<"nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
      }

      if (authorisedActions[i].second == SHIFT_VICTORY)//Higlight = 4 pour moove
      {
        cout<<"Animal VICTORY" <<endl;
        cout<<"anciennes coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
        cout<<"nouvelles coord demandees:" << this->targetCoord.getX() <<","<< this->targetCoord.getY() <<endl;
        this->targetAnimal->setCoord(this->targetCoord);
        engine->getState().setTurn(engine->getState().getTurn()+1);
        cout<<"nouvelles coord:" << this->targetAnimal->getCoord().getX() <<","<< this->targetAnimal->getCoord().getY() <<endl;
        if(engine->getState().getSelection(this->targetAnimal->getCoord()).second == 0){
          engine->getState().setWinner(engine->getState().getPlayer1());
          cout<<"Victoire du Joueur1:"<< engine->getState().getPlayer1().getName() << "BRAVO !!!";
        } else{
          engine->getState().setWinner(engine->getState().getPlayer2());
          cout<<"Victoire du Joueur1:"<< engine->getState().getPlayer2().getName() << "BRAVO !!!";
        }
        engine->getState().setGameover(1);
      }
    }
  }
  cout<<"Passage au tour numéro : " << engine->getState().getTurn() << endl;
}
