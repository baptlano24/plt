#include <iostream>
#include <string> //pour utiliser string::compare

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>

using namespace sf;

void testSFML() {
    sf::Texture texture;
}

// Fin test SFML

#include <state.h>

using namespace std;
using namespace state;

int main(int argc,char* argv[1])
{
    if(argc>=2 && std::string(argv[1])=="hello") {
      cout << "Hello world !" << endl;
    } else {
      cout << "Veuillez dire hello !" << endl;
    }

    if(argc>=2 && std::string(argv[1])=="render") {
      cout << "render !" << endl;
      RenderWindow app(VideoMode(1000, 1000, 32), "Jungle War ?! ");

      // Boucle principale
      while (app.isOpen())
     {
         // check all the window's events that were triggered since the last iteration of the loop
         sf::Event event;
         while (app.pollEvent(event))
         {
             // "close requested" event: we close the window
             if (event.type == Event::Closed)
                 app.close();
         }
         Texture map;
         Sprite sprite;
         map.loadFromFile("../rapport/res/images/map/map-jungle.png");
         sprite.setTexture(map);
         sprite.setScale(0.85,0.85);
         FloatRect spriteSize=sprite.getGlobalBounds();
         //sprite.setOrigin(spriteSize.width/2.,spriteSize.height/2.);
         sprite.setPosition((app.getSize().x-spriteSize.width)/2., (app.getSize().y-spriteSize.height)/2.);
         //sprite.setColor(Color(0,255,0));
         // clear the window with black color
         app.clear(Color::Black);
         app.draw(sprite);
         app.display();
     }

     return 0;
 }
}
