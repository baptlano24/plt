#include "State.h"
#include <iostream>
using namespace std;
using namespace state;
using namespace engine;

State::State(string nom1, string nom2) {
    this->player1 = Player(nom1,0);
    this->player2 = Player(nom2,1);
    this->menu = GAME_MENU;
    this->highlights.push_back(make_pair(Coord {0,0},NONE));

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

menuID& State::getMenu()
{
  menuID& refMenu = this->menu;
  return refMenu;
}

int State::getTurn()
{
  return this->turn;
}

void State::setTurn(int newTurn){
  this->turn = newTurn;
}

const array<array<Square,13>,12>& State::getGrid()
{
  array<array<Square,13>,12>& refGrid = this->grid;
  return refGrid;
}

Square* State::getSquare(Coord Coord)
{
  Square* ptr_Square = NULL;
  if (Coord.getX()<=11 && Coord.getX()>=0 && Coord.getY()<= 12 && Coord.getY()>=0) {
      ptr_Square = &this->grid[Coord.getX()][Coord.getY()];
  }
  return ptr_Square;
}

std::vector<std::pair<state::Coord,engine::ActionID>>& State::getHighlights()
{
  std::vector<std::pair<state::Coord,engine::ActionID>>& refHighlights = this->highlights;
  return refHighlights;
}

void State::setHighlights(std::vector<std::pair<state::Coord,engine::ActionID>>& newHighlights)
{
  this->highlights = newHighlights;
}

pair<Animal*, int> State::getSelection(Coord coord)
{
  pair<Animal*, int> selection;
  selection.first = NULL;
  selection.second = 666;

  for (int i = 0; i<=7 ;i++) {
    if (this->player1.getAnimals()[i].getStatus() == NORMAL && this->player1.getAnimals()[i].getCoord() == coord ) {
      selection.first = &this->player1.getAnimals()[i];
      selection.second = this->player1.getColor();
    }
  }
  for (int i= 0; i<=7 ;i++) {
    if (this->player2.getAnimals()[i].getStatus() == NORMAL && this->player2.getAnimals()[i].getCoord() == coord ) {
      selection.first = &this->player2.getAnimals()[i];
      selection.second = this->player2.getColor();
    }
  }
  return selection;
}
