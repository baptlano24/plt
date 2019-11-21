#include <iostream>
#include "Player.h"
#include "Animal.h"
using namespace std;
using namespace state;

Player::Player() {
    Player("Joueur",3);
}

Player::Player(string name,int color): name(name), color(color)
{
  if (this->color == 0){
    this->animals.push_back(Animal({1,1},NORMAL,RAT)); //(x,y) en haut à gauche
    this->animals.push_back(Animal({2,2},NORMAL,CAT));
    this->animals.push_back(Animal({3,1},NORMAL,DOG));
    this->animals.push_back(Animal({4,2},NORMAL,WOLF));
    this->animals.push_back(Animal({7,2},NORMAL,LEOPARD));
    this->animals.push_back(Animal({8,1},NORMAL,TIGER));
    this->animals.push_back(Animal({9,2},NORMAL,LION));
    this->animals.push_back(Animal({10,1},NORMAL,ELEPHANT));

  }
  else if (this->color == 1){
    this->animals.push_back(Animal({10,11},NORMAL,RAT)); //(x,y) en haut à gauche
    this->animals.push_back(Animal({10,2},NORMAL,CAT)); //9,10
    this->animals.push_back(Animal({11,2},NORMAL,DOG)); //8,11
    this->animals.push_back(Animal({7,10},NORMAL,WOLF));
    this->animals.push_back(Animal({4,10},NORMAL,LEOPARD));
    this->animals.push_back(Animal({3,11},NORMAL,TIGER));
    this->animals.push_back(Animal({2,10},NORMAL,LION)); //2,10
    this->animals.push_back(Animal({1,11},NORMAL,ELEPHANT));
  } else {
    this->animals.push_back(Animal({2,6},NORMAL,RAT)); //(x,y) en haut à gauche
    this->animals.push_back(Animal({3,6},NORMAL,CAT));
    this->animals.push_back(Animal({4,6},NORMAL,DOG));
    this->animals.push_back(Animal({5,6},NORMAL,WOLF));
    this->animals.push_back(Animal({6,6},NORMAL,LEOPARD));
    this->animals.push_back(Animal({7,6},NORMAL,TIGER));
    this->animals.push_back(Animal({8,6},NORMAL,LION));
    this->animals.push_back(Animal({9,6},NORMAL,ELEPHANT));

  }
}

string Player::getName()
{
    return this->name;
}

int Player::getColor()
{
    return this->color;
}

std::vector<Animal>& Player::getAnimals()
{
    return this->animals;
}

void Player::setName(string name)
{
    this->name = name;
}

void Player::setColor(int color)
{
    this->color = color;
}
