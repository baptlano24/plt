#include "State.h"
#include <iostream>
using namespace std;
using namespace state;

State::State(Player player1, Player player2 ): player1(player1), player2(player2) {
    // MAP CONSTRUCTION
    //std::array<std::array<Square,13>,12> newGrid;
    //newGrid[0][0] = Square(true, EARTH);
    //this->grid = newGrid;
}

/*std::array<std::array<Square,13>,12> State:: getGrid()
{
    return this->grid;
}*/

Player State:: getPlayer1()
{
    return this->player1;
}

Player State:: getPlayer2()
{
    return this->player2;
}
