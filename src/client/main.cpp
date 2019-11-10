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

  			sf::RenderWindow window(sf::VideoMode(876,949), "Jungle War");

  			// -- Affichage de cet Etat --
  			RenderLayer stateLayer(initialState, window);

        stateLayer.draw(window);

  } else if (argc>=2 && string(argv[1])=="Engine") {
    cout<<"Lancement de la commande Engine."<<endl;
    Engine engine;
    sf::RenderWindow window(sf::VideoMode(876,949), "Jungle War");
    // FULL SCREEN
    /*int renderWidth = VideoMode::getDesktopMode().width;
    int renderHeight = VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode(renderWidth,renderHeight), "Jungle War");*/
    window.setFramerateLimit(60);
    RenderLayer stateLayer(engine.getState(), window);
    RenderLayer* ptr_stateLayer=&stateLayer;
    engine.getState().registerObserver(ptr_stateLayer);

    bool demarrage = true;
    while (window.isOpen()){
      sf::Event event;
      int mouseX = Mouse::getPosition(window).x;
      int mouseY = Mouse::getPosition(window).y;
      int mouseGridX = mouseX/73;
      int mouseGridY = mouseY/73;
      //cout << mouseX << " : "<< mouseY << endl;
      if (demarrage){
        stateLayer.draw(window);
        cout << "(Cliquez pour simuler un tour de jeu)" << endl << endl;
        demarrage = false;
      }

      while (window.pollEvent(event)){
        if (event.type == Event::Closed){
          window.close();
        }
        else if(event.type == Event::MouseButtonPressed) {
          cout << "Mouse clic wind event : " << mouseX << " , "<< mouseY << endl;
          cout << "Mouse clic grid event : " << mouseGridX << " , "<< mouseGridY << endl << endl;
          Animal &rat = engine.getState().getPlayer1().getAnimals().at(RAT);
          if (mouseGridX == rat.getCoord().getX()) {
            cout << "-- Beginning of the move --" << endl;
            Move move1(rat,Coord(5,5));
            move1.execute(engine.getState());
            StateEvent stateEvent(ALL_CHANGED);
            engine.getState().notifyObservers(stateEvent,engine.getState());
            cout << "-- End of the move --" << endl << endl;
          }
          /*int ligne = 2;

          while(rat.getCoord() != Coord(1,5)){
            Move move(rat,Coord(1,ligne));
            move.execute(engine.getState());
            StateEvent stateEvent(ALL_CHANGED);
            engine.getState().notifyObservers(stateEvent,engine.getState());
            ligne = ligne + 1;
            sleep(1);*/
          }
        }
      }
    } else {
      cout << "Veuillez dire une commande (hello, renderTest1, renderTest2) !" << endl;
    }
  return 0;
}
