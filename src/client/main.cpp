#include <iostream>
#include <string> //pour utiliser string::compare
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <state.h>
#include "state.h"
#include "render.h"
using namespace std;
using namespace state;
using namespace sf;
using namespace render;

void testSFML() {
    Texture texture;
}

int main(int argc,char* argv[1])
{
    if(argc>=2 && string(argv[1])=="hello") {
        cout << "Hello world !" << endl;
    } else if (argc>=2 && string(argv[1])=="renderTest"){
        // Create the main window
        RenderWindow window(VideoMode(876,949), "Jungle War");
        // Load a sprite to display
        Texture texture;
        if (!texture.loadFromFile("../rapport/res/images/map/map-jungle.png"))
            return EXIT_FAILURE;
        Sprite sprite(texture);
        // Create a graphical text to display
        Font font;
        if (!font.loadFromFile("../rapport/res/fonts/sans-serif.ttf"))
            return EXIT_FAILURE;
        Text text("This is our first render", font, 30);

        unordered_map<int, Animal> testAnimals;
        testAnimals.insert(make_pair(1,Animal(10,0)));
        testAnimals.insert(make_pair(2,Animal(1,7)));
        testAnimals.insert(make_pair(3,Animal(3,3)));
        testAnimals.insert(make_pair(4,Animal(4,4)));
        testAnimals.insert(make_pair(5,Animal(5,5)));
        testAnimals.insert(make_pair(6,Animal(6,6)));
        testAnimals.insert(make_pair(7,Animal(7,7)));
        testAnimals.insert(make_pair(8,Animal(8,8)));

        Texture textureAnimal;
        if (!textureAnimal.loadFromFile("../rapport/res/images/game/wood.png"))
            return EXIT_FAILURE;

        Sprite spriteRat(textureAnimal);
        Sprite spriteCat(textureAnimal);
        Sprite spriteDog(textureAnimal);
        Sprite spriteWolf(textureAnimal);
        Sprite spriteLeopard(textureAnimal);
        Sprite spriteTiger(textureAnimal);
        Sprite spriteLion(textureAnimal);
        Sprite spriteElephant(textureAnimal);

        vector<Sprite> spriteAnimals { spriteRat, spriteCat, spriteDog, spriteWolf, spriteLeopard, spriteTiger, spriteLion, spriteElephant};

        for(int index = 0; index<8; index++) {
            spriteAnimals.at(index).setColor(Color(100, 100, 255, 255));
            spriteAnimals.at(index).setScale(0.0792,0.0792);
        }

        for (pair<int, Animal> element : testAnimals) {
            spriteAnimals.at(element.first-1).setPosition(73*element.second.getX(),73*element.second.getY());
        }

        //Center the jungle map
        /*

        FloatRect spriteSize=sprite.getGlobalBounds();
        sprite.setPosition((app.getSize().x-spriteSize.width)/2., (app.getSize().y-spriteSize.height)/2.);
        sprite.setScale(0.85,0.85);
        */

        // Start the game loop
        while (window.isOpen())
        {
            // Process events
            Event event;
            while (window.pollEvent(event))
            {
                // Close window: exit
                if (event.type == Event::Closed)
                    window.close();
            }
            // Clear screen
            window.clear();
            // Draw the sprite
            window.draw(sprite);
            for(int index = 0; index<8; index++) {
                window.draw(spriteAnimals.at(index));
            }
            //window.draw(spriteAnimals[1]);
            // Draw the string
            window.draw(text);
            // Update the window
            window.display();
        }
    } else if (argc>=2 && string(argv[1])=="renderTest2"){
          cout<<"--- Affichage d'un Etat ---"<<endl;

    			// -- Initialisation d'un etat --
    			State initialState;

    			sf::RenderWindow window(sf::VideoMode(876,949), "Jungle War");
    			// -- Affichage de cet Etat --
    			RenderLayer stateLayer(initialState, window);

          stateLayer.draw(window);

    } else {
        cout << "Veuillez dire une commande (hello, render, renderTest, etc..) !" << endl;
    }
    return 0;

}
