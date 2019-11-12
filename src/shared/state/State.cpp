#include "State.h"
#include <iostream>
using namespace std;
using namespace state;

State::State(string nom1, string nom2) {
    this->player1 = Player(nom1,0);
    this->player2 = Player(nom2,1);
    this->menu = GAME_MENU;
    this->grid = array<array<Square,13>,12> {
      array<Square,13> {{EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH}},
      array<Square,13> {{EARTH,EARTH,EARTH,EARTH,EARTH,SHORE,SHORE,SHORE,EARTH,EARTH,EARTH,EARTH,EARTH}},
      array<Square,13> {{EARTH,EARTH,EARTH,EARTH,SHORE,WATER,WATER,WATER,SHORE,EARTH,EARTH,EARTH,EARTH}},
      array<Square,13> {{EARTH,EARTH,EARTH,EARTH,SHORE,WATER,WATER,WATER,SHORE,EARTH,EARTH,EARTH,EARTH}},
      array<Square,13> {{TRAPJ1,EARTH,EARTH,EARTH,SHORE,WATER,WATER,WATER,SHORE,EARTH,EARTH,EARTH,TRAPJ2}},
      array<Square,13> {{THRONEJ1,TRAPJ1,EARTH,EARTH,EARTH,SHORE,SHORE,SHORE,EARTH,EARTH,EARTH,TRAPJ2,THRONEJ2}},
      array<Square,13> {{THRONEJ1,TRAPJ1,EARTH,EARTH,EARTH,SHORE,SHORE,SHORE,EARTH,EARTH,EARTH,TRAPJ2,THRONEJ2}},
      array<Square,13> {{TRAPJ1,EARTH,EARTH,EARTH,SHORE,WATER,WATER,WATER,SHORE,EARTH,EARTH,EARTH,TRAPJ2}},
      array<Square,13> {{EARTH,EARTH,EARTH,EARTH,SHORE,WATER,WATER,WATER,SHORE,EARTH,EARTH,EARTH,EARTH}},
      array<Square,13> {{EARTH,EARTH,EARTH,EARTH,SHORE,WATER,WATER,WATER,SHORE,EARTH,EARTH,EARTH,EARTH}},
      array<Square,13> {{EARTH,EARTH,EARTH,EARTH,EARTH,SHORE,SHORE,SHORE,EARTH,EARTH,EARTH,EARTH,EARTH}},
      array<Square,13> {{EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH,EARTH}}
    };
}

State::State() {
  new (this) State("Joueur1", "Joueur2");
}

Player& State::getPlayer1()
{
  Player& refPlay = this->player1;
  return refPlay;
}

Player& State::getPlayer2()
{
  Player& refPlay = this->player2;
  return refPlay;
}

const array<array<Square,13>,12>& State::getGrid()
{
  array<array<Square,13>,12>& refGrid = this->grid;
  return refGrid;
}

Square& State::getSquare(Coord Coord)
{
  if (Coord.getX()<=11 && Coord.getX()>=0 && Coord.getY()<= 12 && Coord.getY()>=0) {
    Square& refSquare = this->grid[Coord.getX()][Coord.getY()];
    return refSquare;
  } else{
    Square Nomap;
    Nomap.setID(NOMAP);
    Square& refSquare = Nomap;
    return refSquare;
  }
}

pair<Animal&, bool> State::getSelection(Coord coord)
{
  if (coord.getX()<=11 && coord.getX()>=0 && coord.getY()<= 12 && coord.getY()>=0) {
    for (auto &animalPair : this->player1.getAnimals()) {
      if (animalPair.second.getStatus() == NORMAL && animalPair.second.getCoord() == coord ) {
        pair<Animal&, bool> duo(animalPair.second,true);
        return duo;
      }
    }
    for (auto &animalPair : this->player2.getAnimals()) {
      if (animalPair.second.getStatus() == NORMAL && animalPair.second.getCoord() == coord ) {
        pair<Animal&, bool> duo(animalPair.second,true);
        return duo;
      }
    }
  } else {
    Animal noAnimal(Coord(0,0),DEAD);
    
    pair<Animal&, bool> duo(noAnimal,false);
    return duo;
  }
}
