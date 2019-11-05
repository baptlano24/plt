#include <string>
#include "../render.h"

using namespace render;

TileSet::TileSet(TileSetID id){

	this->id=id;

	if (id == INFOS){
		width=73;
		height=73;
		imageFile="../res/images/game/animalsTile.png";
	}

	else if (id==ANIMALS){
		width=73;
		height=73;
		imageFile="../res/images/game/animalsTile.png";
	}

	else if (id==GRID){
		width=876;
		height=949;
		imageFile="../res/images/map/map-jungle.png";
	}

	textureTileSet.loadFromFile(imageFile);
}

TileSetID TileSet::getID(){
	return this->id;
}

const int TileSet::getWidth(){
	return this->width;
}

const int TileSet::getHeight(){
	return this->height;
}

const std::string  TileSet::getImageFile (){
	return this->imageFile;
}

sf::Texture& TileSet::getTexture(){
	sf::Texture & refTexture = this->textureTileSet;
	return refTexture ;
}
