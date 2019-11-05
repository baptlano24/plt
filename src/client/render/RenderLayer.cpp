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
	unique_ptr<TileSet> ptr_tileSetAnimals (new TileSet(tileSetAnimals));
	tileSets.push_back(move(ptr_tileSetAnimals));

  TileSet tileSetGrid(GRID);
  unique_ptr<TileSet> ptr_tileSetGrid (new TileSet(tileSetGrid));
  tileSets.push_back(move(ptr_tileSetGrid));

  Texture textureGrid;
  if (!this->textureGrid.loadFromFile("../res/images/map/map-jungle.png")) {
      cout << "Erreur de chargement de la texture map";
  }

  this->animalsJ1 = this->renderingState.getPlayer1().getAnimals();
  this->animalsJ2 = this->renderingState.getPlayer2().getAnimals();

  if (!this->textureAnimal.loadFromFile("../res/images/game/wood.png"))
      cout << "Erreur de chargement de la texture animal";

  this->animalsSpriteJ1 = mapToSprites(this->animalsJ1, this->renderingState.getPlayer1().getColor());
  this->animalsSpriteJ2 = mapToSprites(this->animalsJ2, this->renderingState.getPlayer2().getColor());
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

vector<Sprite> RenderLayer::mapToSprites(unordered_map<AnimalID,Animal> animalsMap, int color) {
  Sprite sprite_rat(this->textureAnimal);
  Sprite sprite_cat(this->textureAnimal);
  Sprite sprite_dog(this->textureAnimal);
  Sprite sprite_wolf(this->textureAnimal);
  Sprite sprite_leo(this->textureAnimal);
  Sprite sprite_tig(this->textureAnimal);
  Sprite sprite_lio(this->textureAnimal);
  Sprite sprite_ele(this->textureAnimal);

  vector<Sprite> spriteAnimals {sprite_rat,sprite_cat, sprite_dog, sprite_wolf, sprite_leo, sprite_tig, sprite_lio, sprite_ele};

  for(int index = 0; index<8; index++) {
      spriteAnimals.at(index).setScale(0.0792,0.0792);
  }

  for (pair<AnimalID, Animal> element : animalsMap) {
      spriteAnimals.at(element.first-1).setPosition(73*element.second.getCoord().getX(),73*element.second.getCoord().getY());
      if (element.second.getStatus() == NORMAL) {
        if (color ==0) {
            spriteAnimals.at(element.first-1).setColor(Color(100, 100, 255, 255));
        } else {
            spriteAnimals.at(element.first-1).setColor(Color(255, 100, 100, 255));
        }
      } else if (element.second.getStatus() == DEAD) {
          spriteAnimals.at(element.first-1).setColor(Color(255, 100, 100, 0));
      }
  }

return spriteAnimals;
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
    window.draw(this->getGrid());
    for(int index = 0; index<8; index++) {
        window.draw(this->getAnimalsJ1()[index]);
        window.draw(this->getAnimalsJ2()[index]);
    }
    window.display();
  }
}
