#include "State.h"
#include <iostream>
using namespace std;
using namespace state;

State::State(string nom1, string nom2) {
    //Player newPlayer1 = Player(nom1,0,true);
    //Player newPlayer2 = Player(nom2,1,false);
    //this->player1 = newPlayer1;
    //this->player2 = newPlayer2;
}

Player State:: getPlayer1()
{
    return this->player1;
}

Player State:: getPlayer2()
{
    return this->player2;
}
