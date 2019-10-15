#include <iostream>
#include "Player.h"
#include "Animal.h"
#include "AnimalStatus.h"
using namespace std;
using namespace state;

Player::Player()  : name("Joueur"), color(0),  playing(0){
  std::unordered_map<int, Animal> newAnimals;
  newAnimals.insert(make_pair(1,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(2,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(3,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(4,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(5,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(6,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(7,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(8,Animal(0,0,NORMAL)));
  this->animals = newAnimals;
}

Player::Player(string name,int color,bool playing):
name(name), color(color),  playing(playing)
{
  std::unordered_map<int, Animal> newAnimals;
  newAnimals.insert(make_pair(1,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(2,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(3,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(4,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(5,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(6,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(7,Animal(0,0,NORMAL)));
  newAnimals.insert(make_pair(8,Animal(0,0,NORMAL)));

  this->animals = newAnimals;
}

/*Player::Player(Player p) {
    this->name = p.name;
    this->color = p.color;
    this->playing = p.playing;
}*/

string Player:: getName()
{
    return this->name;
}

int Player:: getColor()
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
