#include "RenderLayer.h"
#include "../render.h"
#include <iostream>

using namespace std;
using namespace state;
using namespace sf;
using namespace render;

//RenderLayer::RenderLayer(State& state, RenderWindow& window): window(window) {}

RenderLayer::RenderLayer(state::State& state, sf::RenderWindow& window): window(window){
  Texture textureGrid;
  if (!textureGrid.loadFromFile("../rapport/res/images/map/map-jungle.png")) {
      cout << "Erreur de chargement de la texture map";
  }
  auto ptr_sprite_grid = std::make_shared<sf::Sprite>(textureGrid);
  //std::shared_ptr<sf::Sprite> ptr_sprite_grid (new sf::Sprite(textureGrid));

  unordered_map<int, Animal> testAnimals;
  testAnimals.insert(make_pair(1,Animal(10,0)));
  testAnimals.insert(make_pair(2,Animal(1,7)));
  testAnimals.insert(make_pair(3,Animal(3,3)));
  testAnimals.insert(make_pair(4,Animal(4,4)));
  testAnimals.insert(make_pair(5,Animal(5,5)));
  testAnimals.insert(make_pair(6,Animal(6,6)));
  testAnimals.insert(make_pair(7,Animal(7,7)));
  testAnimals.insert(make_pair(8,Animal(8,8)));

  if (!this->textureAnimal.loadFromFile("../rapport/res/images/game/wood.png"))
      cout << "Erreur de chargement de la texture animal";

  std::shared_ptr<sf::Sprite> ptr_sprite_rat (new sf::Sprite(this->textureAnimal));
  std::shared_ptr<sf::Sprite> ptr_sprite_cat (new sf::Sprite(this->textureAnimal));
  std::shared_ptr<sf::Sprite> ptr_sprite_dog (new sf::Sprite(this->textureAnimal));
  std::shared_ptr<sf::Sprite> ptr_sprite_wolf (new sf::Sprite(this->textureAnimal));
  std::shared_ptr<sf::Sprite> ptr_sprite_leo (new sf::Sprite(this->textureAnimal));
  std::shared_ptr<sf::Sprite> ptr_sprite_tig (new sf::Sprite(this->textureAnimal));
  std::shared_ptr<sf::Sprite> ptr_sprite_lio (new sf::Sprite(this->textureAnimal));
  std::shared_ptr<sf::Sprite> ptr_sprite_ele (new sf::Sprite(this->textureAnimal));

  vector<std::shared_ptr<sf::Sprite>> spriteAnimals { ptr_sprite_rat,
                                                      ptr_sprite_cat,
                                                      ptr_sprite_dog,
                                                      ptr_sprite_wolf,
                                                      ptr_sprite_leo,
                                                      ptr_sprite_tig,
                                                      ptr_sprite_lio,
                                                      ptr_sprite_ele};

  for(int index = 0; index<8; index++) {
      spriteAnimals.at(index)->setColor(Color(100, 100, 255, 255));
      spriteAnimals.at(index)->setScale(0.0792,0.0792);
  }

  for (pair<int, Animal> element : testAnimals) {
      spriteAnimals.at(element.first-1)->setPosition(73*element.second.getX(),73*element.second.getY());
  }

  this->grid = ptr_sprite_grid;
  this->animals = spriteAnimals;
};

vector<std::shared_ptr<sf::Sprite>> RenderLayer::getAnimals(){
  return this->animals;
};

std::shared_ptr<sf::Sprite> RenderLayer::getGrid() {
  return this->grid;
};


void RenderLayer::draw(sf::RenderWindow &window) {
  while (window.isOpen()){
    Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
    }

    window.clear();
    //window.draw(*stateLayer.getAnimals());	// Dessin de la grille
    window.draw(*this->getGrid());
    for(int index = 0; index<8; index++) {
        window.draw(*this->getAnimals()[index]);
    }
    //window.draw(*layer.getSurfaces()[1]);	// Dessin des personnages
    window.display();
  }
}
