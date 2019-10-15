#include "State.h"
#include <iostream>
using namespace std;
using namespace state;

State::State(){
  this->player1 = Player();
  this->player2 = Player();
  std::array<std::array<Square,13>,12> newGrid;
  this->grid = newGrid;

}
State::State(string nom1, string nom2) {
    this->player1 = Player(nom1,0,true);
    this->player2 = Player(nom2,1,false);

    //Map creation
    std::array<std::array<Square,13>,12> newGrid;
    //THRONES
    newGrid[0][5].setID(THRONEJ1);
    newGrid[0][6].setID(THRONEJ1);
    newGrid[11][5].setID(THRONEJ2);
    newGrid[11][6].setID(THRONEJ2);
    //TRAPS
    newGrid[0][4].setID(TRAPJ1);
    newGrid[0][7].setID(TRAPJ1);
    newGrid[1][5].setID(TRAPJ1);
    newGrid[1][6].setID(TRAPJ1);
    newGrid[-1][4].setID(TRAPJ2);
    newGrid[-1][7].setID(TRAPJ2);
    newGrid[11][5].setID(TRAPJ2);
    newGrid[11][6].setID(TRAPJ2);
    //SHORE
    newGrid[2][4].setID(SHORE); //Horizontaly
    newGrid[3][4].setID(SHORE);
    newGrid[4][4].setID(SHORE);
    newGrid[2][8].setID(SHORE);
    newGrid[3][8].setID(SHORE);
    newGrid[4][8].setID(SHORE);
    newGrid[7][4].setID(SHORE);
    newGrid[8][4].setID(SHORE);
    newGrid[9][4].setID(SHORE);
    newGrid[7][8].setID(SHORE);
    newGrid[8][8].setID(SHORE);
    newGrid[9][8].setID(SHORE);
    newGrid[1][5].setID(SHORE); //Verticaly
    newGrid[1][6].setID(SHORE);
    newGrid[1][7].setID(SHORE);
    newGrid[5][5].setID(SHORE);
    newGrid[5][6].setID(SHORE);
    newGrid[5][7].setID(SHORE);
    newGrid[6][5].setID(SHORE);
    newGrid[6][6].setID(SHORE);
    newGrid[6][7].setID(SHORE);
    newGrid[10][5].setID(SHORE);
    newGrid[10][6].setID(SHORE);
    newGrid[10][7].setID(SHORE);
    //WATER
        for(int x = 2; x<=4; x++){
          for (int y= 5; y<=7; y++){
              newGrid[x][y].setID(WATER);
          }
        }
        for(int x = 7; x<=9; x++){
          for (int y= 5; y<=7; y++){
              newGrid[x][y].setID(WATER);
          }
        }
    this->grid = newGrid;
}

Player State:: getPlayer1()
{
    return this->player1;
}

Player State:: getPlayer2()
{
    return this->player2;
}
