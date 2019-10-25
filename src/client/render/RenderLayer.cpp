#include "RenderLayer.h"
#include "../render.h"
#include <iostream>

using namespace std;
using namespace state;
using namespace sf;
using namespace render;


RenderLayer::RenderLayer(state::State& state, RenderWindow& window): window(window){
  this->renderingState = state;

  TileSet tileSetAnimals(ANIMALS);
	std::unique_ptr<TileSet> ptr_tileSetAnimals (new TileSet(tileSetAnimals));
	tileSets.push_back(move(ptr_tileSetAnimals));

  TileSet tileSetGrid(GRID);
  std::unique_ptr<TileSet> ptr_tileSetGrid (new TileSet(tileSetGrid));
  tileSets.push_back(move(ptr_tileSetGrid));

  Texture textureGrid;
  if (!this->textureGrid.loadFromFile("../rapport/res/images/map/map-jungle.png")) {
      cout << "Erreur de chargement de la texture map";
  }

  //shared_ptr<Sprite> ptr_sprite_grid (new Sprite(textureGrid));
  this->animalsJ1 = this->renderingState.getPlayer1().getAnimals();
  this->animalsJ2 = this->renderingState.getPlayer2().getAnimals();

  unordered_map<int, Animal> testAnimals;
  testAnimals.insert(make_pair(1,Animal(2,2)));
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

  vector<Sprite> spriteAnimalsJ1 {sprite_rat,sprite_cat, sprite_dog, sprite_wolf, sprite_leo, sprite_tig, sprite_lio, sprite_ele};
  vector<Sprite> spriteAnimalsJ2 {sprite_rat, sprite_cat, sprite_dog, sprite_wolf, sprite_leo, sprite_tig, sprite_lio, sprite_ele};

  for(int index = 0; index<8; index++) {
      spriteAnimalsJ1.at(index).setColor(Color(100, 100, 255, 255));
      spriteAnimalsJ1.at(index).setScale(0.0792,0.0792);
      spriteAnimalsJ2.at(index).setColor(Color(200, 100, 255, 255));
      spriteAnimalsJ2.at(index).setScale(0.0792,0.0792);
  }

  for (pair<int, Animal> element : this->animalsJ1) {
      spriteAnimalsJ1.at(element.first-1).setPosition(73*element.second.getX(),73*element.second.getY());
  }
  for (pair<int, Animal> element : this->animalsJ2) {
      spriteAnimalsJ2.at(element.first-1).setPosition(73*element.second.getX(),73*element.second.getY());
  }

  this->animalsSpriteJ1 = spriteAnimalsJ1;
  this->animalsSpriteJ2 = spriteAnimalsJ2;
  this->spriteGrid = Sprite(this->textureGrid);
};

vector<Sprite> RenderLayer::getAnimalsJ1(){
  return this->animalsSpriteJ1;
};

vector<Sprite> RenderLayer::getAnimalsJ2(){
  return this->animalsSpriteJ2;
};

Sprite RenderLayer::getGrid() {
   return (this->spriteGrid);
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
        window.draw(this->getAnimalsJ1()[index]);
        window.draw(this->getAnimalsJ2()[index]);
    }
    //window.draw(*layer.getSurfaces()[1]);	// Dessin des personnages
    window.display();
  }
}
