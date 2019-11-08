#include <iostream>
#include "Player.h"
#include "Animal.h"
#include "AnimalStatus.h"
using namespace std;
using namespace state;

Player::Player() {
    Player("Joueur",0);
}

Player::Player(string name,int color): name(name), color(color)
{
  if (this->color == 0){
    std::unordered_map<AnimalID, Animal> newAnimals;
    newAnimals.insert(make_pair(RAT,Animal({1,1},NORMAL))); //(x,y) en haut à gauche
    newAnimals.insert(make_pair(CAT,Animal({2,2},NORMAL)));
    newAnimals.insert(make_pair(DOG,Animal({3,1},NORMAL)));
    newAnimals.insert(make_pair(WOLF,Animal({4,2},NORMAL)));
    newAnimals.insert(make_pair(LEOPARD,Animal({7,2},NORMAL)));
    newAnimals.insert(make_pair(TIGER,Animal({8,1},NORMAL)));
    newAnimals.insert(make_pair(LION,Animal({9,2},NORMAL)));
    newAnimals.insert(make_pair(ELEPHANT,Animal({10,1},NORMAL)));
    this->animals = newAnimals;
  }
  else if (this->color == 1){
    std::unordered_map<AnimalID, Animal> newAnimals;
    newAnimals.insert(make_pair(RAT,Animal({10,11},NORMAL))); //(x,y) en haut à gauche
    newAnimals.insert(make_pair(CAT,Animal({9,10},NORMAL)));
    newAnimals.insert(make_pair(DOG,Animal({8,11},NORMAL)));
    newAnimals.insert(make_pair(WOLF,Animal({7,10},NORMAL)));
    newAnimals.insert(make_pair(LEOPARD,Animal({4,10},NORMAL)));
    newAnimals.insert(make_pair(TIGER,Animal({3,11},NORMAL)));
    newAnimals.insert(make_pair(LION,Animal({2,10},NORMAL)));
    newAnimals.insert(make_pair(ELEPHANT,Animal({1,11},NORMAL)));
    this->animals = newAnimals;
  } else {
    std::unordered_map<AnimalID, Animal> newAnimals;
    newAnimals.insert(make_pair(RAT,Animal({2,6},NORMAL))); //(x,y) en haut à gauche
    newAnimals.insert(make_pair(CAT,Animal({3,6},NORMAL)));
    newAnimals.insert(make_pair(DOG,Animal({4,6},NORMAL)));
    newAnimals.insert(make_pair(WOLF,Animal({5,6},NORMAL)));
    newAnimals.insert(make_pair(LEOPARD,Animal({6,6},NORMAL)));
    newAnimals.insert(make_pair(TIGER,Animal({7,6},NORMAL)));
    newAnimals.insert(make_pair(LION,Animal({8,6},NORMAL)));
    newAnimals.insert(make_pair(ELEPHANT,Animal({9,6},NORMAL)));
    this->animals = newAnimals;
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

unordered_map<AnimalID, Animal>& Player::getAnimals()
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
