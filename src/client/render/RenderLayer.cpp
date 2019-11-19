#include "RenderLayer.h"
#include "../render.h"
#include <iostream>

using namespace std;
using namespace state;
using namespace sf;
using namespace render;


RenderLayer::RenderLayer(state::State& state, RenderWindow& window): window(window){

    if (!this->textureGrid.loadFromFile("../res/images/map/map-jungle.png")) {
        cout << "Erreur de chargement de la texture à partir de map-jungle";
    };

    for(int animal_index = 0; animal_index<8; ++animal_index) {
        Texture animal;
        animal.setSmooth(true);
        if(!animal.loadFromFile("../res/images/game/animalsTile.png", sf::IntRect(animal_index*400, 0, 400, 400))) {
           cout << "Erreur de chargement de la texture à partir d'animalsTile" << animal_index;
        };
        this->texturesAnimals.push_back(animal);
    };

    updateRender(state);
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

void RenderLayer::updateRender(const state::State& newState){
  this->renderingState = newState;
  this->animalsSpriteJ1 = mapToSprites(this->renderingState.getPlayer1().getAnimals(), this->renderingState.getPlayer1().getColor());
  this->animalsSpriteJ2 = mapToSprites(this->renderingState.getPlayer2().getAnimals(), this->renderingState.getPlayer2().getColor());
}

void RenderLayer::stateChanged (const state::StateEvent& e, const state::State& newState){
	updateRender(newState);
	draw(window);
}

vector<Sprite> RenderLayer::mapToSprites(vector<state::Animal>& animalsMap, int color) {
    vector<Sprite> spriteAnimals;
    for (const auto &texture : this->texturesAnimals) {
        spriteAnimals.push_back(Sprite {texture});
    }
    for(auto &sprite : spriteAnimals) {
        sprite.setScale(0.1825,0.1825);
    }
    for (int i = 0; i <= 7; i++) {
        spriteAnimals[i].setPosition(73*animalsMap[i].getCoord().getX(),73*animalsMap[i].getCoord().getY());
        if (animalsMap[i].getStatus() == NORMAL) {
            if (color == 0) {
                spriteAnimals[i].setColor(Color(180, 180, 255, 255));
            } else {
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
  }
  window.display();
}
