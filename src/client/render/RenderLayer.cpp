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
  this->animalsJ1 = this->renderingState.getPlayer1().getAnimals();
  this->animalsJ2 = this->renderingState.getPlayer2().getAnimals();
  this->animalsSpriteJ1 = mapToSprites(this->animalsJ1, this->renderingState.getPlayer1().getColor());
  this->animalsSpriteJ2 = mapToSprites(this->animalsJ2, this->renderingState.getPlayer2().getColor());
}

void RenderLayer::stateChanged (const state::StateEvent& e, const state::State& newState){
	updateRender(newState);
	draw(window);
}

vector<Sprite> RenderLayer::mapToSprites(unordered_map<AnimalID,Animal> animalsMap, int color) {
    vector<Sprite> spriteAnimals;
    for (const auto &texture : this->texturesAnimals) {
        spriteAnimals.push_back(Sprite {texture});
    }
    for(auto &sprite : spriteAnimals) {
        sprite.setScale(0.1825,0.1825);
    }
    for (const pair<AnimalID, Animal> &element : animalsMap) {
        spriteAnimals.at(element.first-1).setPosition(73*element.second.getCoord().getX(),73*element.second.getCoord().getY());
        if (element.second.getStatus() == NORMAL) {
            if (color ==0) {
                spriteAnimals.at(element.first-1).setColor(Color(180, 180, 255, 255));
            } else {
                spriteAnimals.at(element.first-1).setColor(Color(255, 180, 180, 255));
            }
        } else if (element.second.getStatus() == DEAD) {
            spriteAnimals.at(element.first-1).setColor(Color(255, 180, 180, 0));
        }
    }
return spriteAnimals;
};

void RenderLayer::draw(RenderWindow &window) {
    window.clear();
    window.draw(this->getGrid());
    for(int index = 0; index<8; index++) {
        window.draw(this->getAnimalsJ1()[index]);
        window.draw(this->getAnimalsJ2()[index]);
    }
    window.display();
}
