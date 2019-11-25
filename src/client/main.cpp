#include <iostream>
#include <string> //pour utiliser string::compare
#include <utility>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <state.h>
#include "state.h"
#include "render.h"
#include <engine.h>
#include "engine.h"
using namespace std;
using namespace state;
using namespace sf;
using namespace render;
using namespace engine;

int main(int argc,char* argv[1]) {
  if(argc>=2 && string(argv[1])=="hello") {
      /*Engine engine1;
      Coord coord1(9,2);
      std::vector<pair<state::Coord,engine::ActionID>> listAction1;
      listAction1 = engine1.authorisedActions(engine1.getState(),coord1);
      Square* k = engine1.getState().getSquare(coord1);

      for (int i =0; i<=3; i++){
          if(engine1.getState().getSquare(listAction1[i].first)->getID() != WATER){
            cout<<"NOWATER" << endl;
            cout << engine1.getState().getSquare(listAction1[i].first)->getID() << endl;
          }*/
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
    Engine* ptr_engine = &engine;
    sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
    RenderLayer stateLayer(engine.getState(), window);
    RenderLayer* ptr_stateLayer = &stateLayer;

    stateLayer.registerObserver(ptr_engine);
    engine.getState().registerObserver(ptr_stateLayer);
    stateLayer.draw(window);

    int newX = 1;
    int newY = 1;
    int mouseX;
    int mouseY;
    int mouseGridX;
    int mouseGridY;
    Coord mouseCoord;
    Coord targetCoord;
    Coord& refTargetCoord = targetCoord;
    bool animalSelected = false;
    Animal* selectedAnimal;

    while (window.isOpen()){
      Event event;
      mouseX = Mouse::getPosition(window).x;
      mouseY = Mouse::getPosition(window).y;
      mouseGridX = (mouseX-73*3)/73; //73*3 to change by gridOrigine.getX() when in the render
      mouseGridY = mouseY/73;
      mouseCoord.setX(mouseGridX);
      mouseCoord.setY(mouseGridY);

      while (window.pollEvent(event)){
        if (event.type == Event::Closed){
          window.close();
        }

        else if(event.type == Event::MouseButtonPressed) {
          cout << endl << "         * Clic *" << endl;

          if (animalSelected == false) {
            cout << "Selection :" << endl;
            cout << "Mouse clic pixel event : " << mouseX << " , "<< mouseY << endl;
            cout << "Mouse clic grid event : (" << mouseGridX << " , "<< mouseGridY << ")" << endl;
            pair<Animal*, int> selection = engine.getState().getSelection(mouseCoord);
            selectedAnimal = selection.first;
            if (selection.first != 0 && engine.getState().getTurn()%2 == selection.second){
              Select select1(selectedAnimal, mouseCoord);
              select1.execute(ptr_engine);
              StateEvent highlightsChangedEvent(HIGHLIGHTS_CHANGED);
              StateEvent& refHighlightsChangedEvent = highlightsChangedEvent;
              engine.getState().notifyObservers(refHighlightsChangedEvent, engine.getState());
              animalSelected = true;
            }

          } else if ((animalSelected == true)) {
            cout << "-- Beginning of the move --" << endl;
            cout << "Animal selected id: " << selectedAnimal->getID() << endl;
            newX = mouseGridX;
            newY = mouseGridY;
            targetCoord.setX(newX);
            targetCoord.setY(newY);
            Move move1(selectedAnimal, refTargetCoord);
            move1.execute(ptr_engine);
            StateEvent animalChangedEvent(ANIMALS_CHANGED);
            StateEvent& refAnimalChangedEvent = animalChangedEvent;
            StateEvent highlightsChangedEvent(HIGHLIGHTS_CHANGED);
            StateEvent& refHighlightsChangedEvent = highlightsChangedEvent;
            StateEvent infosChangedEvent(INFOS_CHANGED);
            StateEvent& refInfosChangedEvent = infosChangedEvent;
            engine.getState().notifyObservers(refAnimalChangedEvent, engine.getState());
            engine.getState().notifyObservers(refHighlightsChangedEvent, engine.getState());
            engine.getState().notifyObservers(refInfosChangedEvent, engine.getState());
            animalSelected = false;
            cout << "-- End of the move --" << endl;
          }
        }
      }
    }
  } else {
    cout << "Veuillez dire une commande (hello, renderTest1, renderTest2, Engine) !" << endl;
  }
  return 0;
}
