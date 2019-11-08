#include <iostream>
#include <string> //pour utiliser string::compare
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <state.h>
#include "state.h"
#include "render.h"
#include "engine.h"
using namespace std;
using namespace state;
using namespace sf;
using namespace render;
using namespace engine;

void testSFML() {
    Texture texture;
}

int main(int argc,char* argv[1])
{
    if(argc>=2 && string(argv[1])=="hello") {
        cout << "Hello world !" << endl;
    } else if (argc>=2 && string(argv[1])=="renderTest1"){
        cout << "No test renderTest1: try renderTest2." << endl;
    } else if (argc>=2 && string(argv[1])=="renderTest2"){
          cout<<"--- Affichage de l'état initial de jeu ---"<<endl;

    			// -- Initialisation de l'état intial de jeu --
    			State initialState("Robin","Baptiste");

    			sf::RenderWindow window(sf::VideoMode(876,949), "Jungle War");

    			// -- Affichage de cet Etat --
    			RenderLayer stateLayer(initialState, window);

          stateLayer.draw(window);



    } else if (argc>=2 && string(argv[1])=="Engine") {
      cout<<"Moteur"<<endl;
      Engine engine;
      sf::RenderWindow window(sf::VideoMode(876,949), "Jungle War");
      RenderLayer stateLayer(engine.getState(), window);
      RenderLayer* ptr_stateLayer=&stateLayer;
      engine.getState().registerObserver(ptr_stateLayer);

      bool demarrage = true;

      while (window.isOpen()){
        //sf::Event event;

        if (demarrage){
          stateLayer.draw(window);
          cout << "(Appuyez sur une touche pour simuler un tour de jeu)" << endl;
          cout << "(Cette simulation compte 3 tours)\n" << endl;
          demarrage = false;
        }
      }






    } else {
        cout << "Veuillez dire une commande (hello, renderTest1, renderTest2) !" << endl;
    }
    return 0;

}
