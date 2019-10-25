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
    newAnimals.insert(make_pair(1,Animal(0,0,NORMAL))); //(x,y) en haut à gauche
    newAnimals.insert(make_pair(2,Animal(1,1,NORMAL)));
    newAnimals.insert(make_pair(3,Animal(2,2,NORMAL)));
    newAnimals.insert(make_pair(4,Animal(5,2,NORMAL)));
    newAnimals.insert(make_pair(5,Animal(6,2,NORMAL)));
    newAnimals.insert(make_pair(6,Animal(11,0,NORMAL)));
    newAnimals.insert(make_pair(7,Animal(11,3,NORMAL)));
    newAnimals.insert(make_pair(8,Animal(9,3,NORMAL)));
    this->animals = newAnimals;
  }

  else if (this->color == 1){
    std::unordered_map<int, Animal> newAnimals;
    newAnimals.insert(make_pair(1,Animal(0,12,NORMAL))); //(x,y) en haut à gauche
    newAnimals.insert(make_pair(2,Animal(1,11,NORMAL)));
    newAnimals.insert(make_pair(3,Animal(2,10,NORMAL)));
    newAnimals.insert(make_pair(4,Animal(5,10,NORMAL)));
    newAnimals.insert(make_pair(5,Animal(6,10,NORMAL)));
    newAnimals.insert(make_pair(6,Animal(11,12,NORMAL)));
    newAnimals.insert(make_pair(7,Animal(11,9,NORMAL)));
    newAnimals.insert(make_pair(8,Animal(9,9,NORMAL)));
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
