#include "RenderLayer.h"
#include "../render.h"
#include <iostream>

using namespace std;
using namespace state;
using namespace sf;
using namespace render;

//RenderLayer::RenderLayer(State& state, RenderWindow& window): window(window) {}

RenderLayer::RenderLayer(state::State& state, RenderWindow& window): window(window){
  Texture textureGrid;
  if (!this->textureGrid.loadFromFile("../rapport/res/images/map/map-jungle.png")) {
      cout << "Erreur de chargement de la texture map";
  }

  //shared_ptr<Sprite> ptr_sprite_grid (new Sprite(textureGrid));

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
  Sprite sprite_rat(this->textureAnimal);
  Sprite sprite_cat(this->textureAnimal);
  Sprite sprite_dog(this->textureAnimal);
  Sprite sprite_wolf(this->textureAnimal);
  Sprite sprite_leo(this->textureAnimal);
  Sprite sprite_tig(this->textureAnimal);
  Sprite sprite_lio(this->textureAnimal);
  Sprite sprite_ele(this->textureAnimal);

  vector<Sprite> spriteAnimals {sprite_rat,
                                                      sprite_cat,
                                                      sprite_dog,
                                                      sprite_wolf,
                                                      sprite_leo,
                                                      sprite_tig,
                                                      sprite_lio,
                                                      sprite_ele};

  for(int index = 0; index<8; index++) {
      spriteAnimals.at(index).setColor(Color(100, 100, 255, 255));
      spriteAnimals.at(index).setScale(0.0792,0.0792);
  }

  for (pair<int, Animal> element : testAnimals) {
      spriteAnimals.at(element.first-1).setPosition(73*element.second.getX(),73*element.second.getY());
  }

  this->animals = spriteAnimals;
  this->spritegrid = Sprite(this->textureGrid);
};

vector<Sprite> RenderLayer::getAnimals(){
  return this->animals;
};

Sprite RenderLayer::getGrid() {
   return (this->spritegrid);
};


void RenderLayer::draw(RenderWindow &window) {
  while (window.isOpen()){
    Event event;
    while (window.pollEvent(event)){
      if (event.type == Event::Closed){
        window.close();
      }
    }

    window.clear();
    //window.draw(*stateLayer.getAnimals());	// Dessin de la grille
    window.draw(this->getGrid());
    for(int index = 0; index<8; index++) {
        window.draw(this->getAnimals()[index]);
    }
    //window.draw(*layer.getSurfaces()[1]);	// Dessin des personnages
    window.display();
  }
}
