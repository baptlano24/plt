#include "RenderLayer.h"
#include "../render.h"
#include <iostream>

using namespace std;
using namespace state;
using namespace sf;
using namespace render;

RenderLayer::RenderLayer(state::State& state, RenderWindow& window): window(window){

  this->gridOrigin = Coord(73*3, 0);

  if (!this->textureGrid.loadFromFile("../res/images/map/map-jungle.png")) {
      cout << "Erreur de chargement de la texture à partir de map-jungle";
  };

  for(int animal_index = 0; animal_index<=7; ++animal_index) {
      Texture animal;
      animal.setSmooth(true);
      if(!animal.loadFromFile("../res/images/game/animalsTile.png", IntRect(animal_index*400, 0, 400, 400))) {
         cout << "Erreur de chargement de la texture à partir d'animalsTile" << animal_index;
      };
      this->texturesAnimals.push_back(animal);
  };

  for(int info_index = 0; info_index<=1; ++info_index) {
      Texture info;
      info.setSmooth(true);
      if(!info.loadFromFile("../res/images/game/infosTile.png", IntRect(info_index*219, 0, 219, 219))) {
         cout << "Erreur de chargement de la texture à partir d'infosTile" << info_index;
      };
      this->texturesInfos.push_back(info);
  };

  this->spriteGrid = Sprite(this->textureGrid);
  this->spriteGrid.setPosition(this->gridOrigin.getX(),this->gridOrigin.getY());

  this->updateAllRender();
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

void RenderLayer::stateChanged (state::StateEvent& event, const state::State& newState){
  this->renderingState = newState;
  if (event.getID() == ALL_CHANGED){
    updateAllRender();
  } else if (event.getID() == ANIMALS_CHANGED){
    updateAnimals();
  } else if (event.getID() == INFOS_CHANGED){
    updateInfos();
  } else if (event.getID() == HIGHLIGHTS_CHANGED){
    updateHighlights();
  }
	draw(window);
}

void RenderLayer::updateAllRender() {
    updateAnimals();
    updateInfos();
    updateHighlights();
}

void RenderLayer::updateInfos(){
  cout << "{ Réaffichage des informations de jeu }"<< endl;
  for (const auto &texture : this->texturesInfos) {
      this->spritesInfos.push_back(Sprite {texture});
  }
  for(auto &sprite : spritesInfos) {
      sprite.setScale(0.3333,0.3333);
  }
  for (int i = 0; i <= 1; i++) {
      this->spritesInfos[i].setPosition(this->gridOrigin.getX()-73, 0);
  }
  this->spritesInfos[0].setColor(Color(180, 180, 255, 255));
  this->spritesInfos[1].setColor(Color(255, 180, 180, 255));
}

void RenderLayer::updateHighlights(){
  cout << "{ Réaffichage des cases en surbrillance }"<< endl;
}

void RenderLayer::updateAnimals(){
  cout << "{ Réaffichage des animaux }"<< endl;
  this->animalsSpriteJ1 = vectToSprites(this->renderingState.getPlayer1().getAnimals(), this->renderingState.getPlayer1().getColor());
  this->animalsSpriteJ2 = vectToSprites(this->renderingState.getPlayer2().getAnimals(), this->renderingState.getPlayer2().getColor());
}

vector<Sprite> RenderLayer::vectToSprites(vector<state::Animal>& animalsMap, int color) {
    vector<Sprite> spriteAnimals;
    for (const auto &texture : this->texturesAnimals) {
        spriteAnimals.push_back(Sprite {texture});
    }
    for(auto &sprite : spriteAnimals) {
        sprite.setScale(0.1825,0.1825);
    }
    for (int i = 0; i <= 7; i++) {
        spriteAnimals[i].setPosition(this->gridOrigin.getX() + 73*animalsMap[i].getCoord().getX() ,
                                     this->gridOrigin.getY() + 73*animalsMap[i].getCoord().getY() );
        if (animalsMap[i].getStatus() == NORMAL) {
            if (color == 1) {
                spriteAnimals[i].setColor(Color(180, 180, 255, 255));
            } else if (color == 0) {
                spriteAnimals[i].setColor(Color(255, 180, 180, 255));
            }
        } else if (animalsMap[i].getStatus() == DEAD) {
            spriteAnimals[i].setColor(Color(255, 180, 180, 0));
        }
    }
return spriteAnimals;
};

void RenderLayer::draw(RenderWindow &window) {
  window.clear();
  if (this->renderingState.getMenu() == GAME_MENU){
    window.draw(this->spriteGrid);
    for(int index = 0; index<=7; index++) {
      window.draw(this->animalsSpriteJ1[index]);
      window.draw(this->animalsSpriteJ2[index]);
    }
    if (this->renderingState.getTurn()%2 == 1) {
      window.draw(this->spritesInfos[0]);
    } else if (this->renderingState.getTurn()%2 == 0) {
      window.draw(this->spritesInfos[1]);
    }
  }
  window.display();
}
