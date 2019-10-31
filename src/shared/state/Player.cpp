#include <iostream>
#include "Player.h"
#include "Animal.h"
#include "AnimalStatus.h"
using namespace std;
using namespace state;

Player::Player(): name("Joueur"), color(0),  playing(0)
{
  std::unordered_map<int, Animal> newAnimals;
  newAnimals.insert(make_pair(1,Animal(0,1,NORMAL)));
  newAnimals.insert(make_pair(2,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(3,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(4,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(5,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(6,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(7,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(8,Animal(0,0,NORMAL)));
  this->animals = newAnimals;
}

Player::Player(string name,int color,bool playing): name(name), color(color),  playing(playing)
{
  if (this->color == 0){
    std::unordered_map<int, Animal> newAnimals;
    newAnimals.insert(make_pair(1,Animal(1,1,NORMAL))); //(x,y) en haut à gauche
    newAnimals.insert(make_pair(2,Animal(2,2,NORMAL)));
    newAnimals.insert(make_pair(3,Animal(3,1,NORMAL)));
    newAnimals.insert(make_pair(4,Animal(4,2,NORMAL)));
    newAnimals.insert(make_pair(5,Animal(7,2,NORMAL)));
    newAnimals.insert(make_pair(6,Animal(8,1,TRAPPED)));
    newAnimals.insert(make_pair(7,Animal(9,2,DEAD)));
    newAnimals.insert(make_pair(8,Animal(10,1,NORMAL)));
    this->animals = newAnimals;
  }

  else if (this->color == 1){
    std::unordered_map<int, Animal> newAnimals;
    newAnimals.insert(make_pair(1,Animal(10,11,NORMAL))); //(x,y) en haut à gauche
    newAnimals.insert(make_pair(2,Animal(9,10,NORMAL)));
    newAnimals.insert(make_pair(3,Animal(8,11,NORMAL)));
    newAnimals.insert(make_pair(4,Animal(7,10,NORMAL)));
    newAnimals.insert(make_pair(5,Animal(4,10,NORMAL)));
    newAnimals.insert(make_pair(6,Animal(3,11,NORMAL)));
    newAnimals.insert(make_pair(7,Animal(2,10,NORMAL)));
    newAnimals.insert(make_pair(8,Animal(1,11,NORMAL)));
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

bool Player::getPlaying()
{
    return this->playing;
}

std::unordered_map<int, Animal> Player::getAnimals()
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

void Player::setPlaying(bool playing)
{
    this->playing = playing;
}
