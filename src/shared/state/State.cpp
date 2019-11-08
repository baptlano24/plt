#include "State.h"
#include <iostream>
using namespace std;
using namespace state;

State::State(string nom1, string nom2) {
    this->player1 = Player(nom1,0);
    this->player2 = Player(nom2,1);
    this->menu = GAME_MENU;
    this->grid = std::array<std::array<Square,13>,12> {
      std::array<Square,13> {{EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH}},
      std::array<Square,13> {{EARTH,EARTH,EARTH,EARTH,EARTH,SHORE,SHORE,SHORE,EARTH,EARTH,EARTH,EARTH,EARTH}},
      std::array<Square,13> {{EARTH,EARTH,EARTH,EARTH,SHORE,WATER,WATER,WATER,SHORE,EARTH,EARTH,EARTH,EARTH}},
      std::array<Square,13> {{EARTH,EARTH,EARTH,EARTH,SHORE,WATER,WATER,WATER,SHORE,EARTH,EARTH,EARTH,EARTH}},
      std::array<Square,13> {{TRAPJ1,EARTH,EARTH,EARTH,SHORE,WATER,WATER,WATER,SHORE,EARTH,EARTH,EARTH,TRAPJ2}},
      std::array<Square,13> {{THRONEJ1,TRAPJ1,EARTH,EARTH,EARTH,SHORE,SHORE,SHORE,EARTH,EARTH,EARTH,TRAPJ2,THRONEJ2}},
      std::array<Square,13> {{THRONEJ1,TRAPJ1,EARTH,EARTH,EARTH,SHORE,SHORE,SHORE,EARTH,EARTH,EARTH,TRAPJ2,THRONEJ2}},
      std::array<Square,13> {{TRAPJ1,EARTH,EARTH,EARTH,SHORE,WATER,WATER,WATER,SHORE,EARTH,EARTH,EARTH,TRAPJ2}},
      std::array<Square,13> {{EARTH,EARTH,EARTH,EARTH,SHORE,WATER,WATER,WATER,SHORE,EARTH,EARTH,EARTH,EARTH}},
      std::array<Square,13> {{EARTH,EARTH,EARTH,EARTH,SHORE,WATER,WATER,WATER,SHORE,EARTH,EARTH,EARTH,EARTH}},
      std::array<Square,13> {{EARTH,EARTH,EARTH,EARTH,EARTH,SHORE,SHORE,SHORE,EARTH,EARTH,EARTH,EARTH,EARTH}},
      std::array<Square,13> {{EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH}}
    };
}

State::State() {
    new (this) State("Joueur1", "Joueur2");
}

Player& State:: getPlayer1()
{
    Player& refPlay = this->player1;
    return refPlay;
}

Player& State:: getPlayer2()
{

  Player& refPlay = this->player2;
  return refPlay;
}

Square& State:: getSquare(Coord Coord)
{
  Square& refSquare = this->grid[Coord.getX()][Coord.getY()];
  return refSquare;
}
