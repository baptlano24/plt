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

int main(int argc,char* argv[1]) {
  if(argc>=2 && string(argv[1])=="hello") {
      cout << "Hello world !" << endl;
  } else if (argc>=2 && string(argv[1])=="renderTest1"){
      cout << "La commande renderTest1 est obsolète." << endl;
  } else if (argc>=2 && string(argv[1])=="renderTest2"){
        cout<<"La commande renderTest2 est obsolète."<<endl;
        cout<<"--- Affichage de l'état initial de jeu ---"<<endl;

  			// -- Initialisation de l'état intial de jeu --
  			State initialState("Robin","Baptiste");

  			sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");

  			// -- Affichage de cet Etat --
  			RenderLayer stateLayer(initialState, window);

        stateLayer.draw(window);

  } else if (argc>=2 && string(argv[1])=="Engine") {
    cout<<"Lancement de la commande Engine."<<endl;
    Engine engine;
    sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
    // FULL SCREEN
    /*int renderWidth = VideoMode::getDesktopMode().width;
    int renderHeight = VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(renderWidth,renderHeight), "Jungle War");*/
    RenderLayer stateLayer(engine.getState(), window);
    RenderLayer* ptr_stateLayer=&stateLayer;
    engine.getState().registerObserver(ptr_stateLayer);

    stateLayer.draw(window);

    int newX = 1;
    int newY = 1;
    int mouseX;
    int mouseY;
    int mouseGridX;
    int mouseGridY;
    Coord mouseCoord;
    bool animalSelected = false;
    Animal* selectedAnimal;

    while (window.isOpen()){
      Event event;
      mouseX = Mouse::getPosition(window).x;
      mouseY = Mouse::getPosition(window).y;
      mouseGridX = (mouseX-73*3)/73;
      mouseGridY = mouseY/73;
      mouseCoord.setX(mouseGridX);
      mouseCoord.setY(mouseGridY);

      while (window.pollEvent(event)){
        if (event.type == Event::Closed){
          window.close();
        }

        else if(event.type == Event::MouseButtonPressed) {
          cout << "* Clic *" << endl;

          if (animalSelected == false ) {
            cout << "Selection :" << endl;
            cout << "Mouse clic wind event : " << mouseX << " , "<< mouseY << endl;
            cout << "Mouse clic grid event : (" << mouseGridX << " , "<< mouseGridY << ")" << endl << endl;
            pair<Animal*, int> selection = engine.getState().getSelection(mouseCoord);
            selectedAnimal = selection.first;
            if (selection.first != 0){
              animalSelected = true;
            }

          } else if (animalSelected == true) {
            cout << "-- Beginning of the move --" << endl;
            cout << "Animal selected id: " << selectedAnimal->getID() << endl;
            newX = mouseGridX;
            newY = mouseGridY;
            Move move1(selectedAnimal, Coord(newX,newY));
            move1.execute(engine.getState());
            StateEvent allChangedEvent(ALL_CHANGED);
            engine.getState().notifyObservers(allChangedEvent, engine.getState());
            animalSelected = false;
            cout << "-- End of the move --" << endl << endl;
          }
        }
      }
    }
  } else {
    cout << "Veuillez dire une commande (hello, renderTest1, renderTest2, Engine) !" << endl;
  }
  return 0;
}
