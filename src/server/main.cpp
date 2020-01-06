#include <iostream>
#include <fstream>
#include <string> //pour utiliser string::compare
#include <utility>
#include <unistd.h>
#include <unordered_map>
#include <vector>
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#include "state.h"
#include "../client/render.h"
#include "engine.h"
#include "ai.h"
using namespace std;
using namespace state;
using namespace sf;
using namespace render;
using namespace engine;
using namespace ai;

int delai = 300000 ;
void recordheuristicVSheuristic();

int main(int argc,char* argv[1]) {
  if(argc>=2 && string(argv[1])=="hello") {
    cout << "Hello world !" << endl;
  }
  else if (argc>=2 && string(argv[1])=="record") {
    recordheuristicVSheuristic();
  }}


void recordheuristicVSheuristic(){
    std::string files_order = "../res/replay.txt";
    std::ofstream files_writte(files_order, ios::out|ios::trunc);
    Engine engine;
    Engine* ptr_engine = &engine;
    sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
    RenderLayer stateLayer(engine.getState(), window);
    RenderLayer* ptr_stateLayer = &stateLayer;
    HeuristicAI heuristicAI0(0);
    HeuristicAI heuristicAI1(1);
    engine.setEnableRecord(true);
    stateLayer.registerObserver(ptr_engine);
    engine.getState().registerObserver(ptr_stateLayer);
    stateLayer.draw(window);
    srand (time(NULL));

    while (window.isOpen()){
      Event event;
      while (window.pollEvent(event)){
        if (event.type == Event::Closed){
          window.close();
        }
      }

      if(engine.getState().getGameover() != true){
        if(engine.getState().getPlaying() == 0) {
          cout << endl << "         * IA HeuristicAI0 is playing *" << endl;
          cout<<"Tour numéro : " << engine.getState().getTurn() << endl;
          usleep(delai);
          heuristicAI0.play(ptr_engine);


        } else {
          cout << endl << "         * IA HeuristicAI1 is playing *" << endl;
          cout<<"Tour numéro : " << engine.getState().getTurn() << endl;
          usleep(delai);
          heuristicAI1.play(ptr_engine);

        }
      }
      if(engine.getState().getTurn()> 6) {
        std::ofstream files_writte(files_order, ios::out|ios::trunc);
          if(files_writte){
            cout << "--> Debut de l'enregistrement dans le fichier <--" << endl;

            Json::Value root = engine.getRecord();
            cout << root << endl;

            // Ecriture dans le fichier du tableau de commandes de cette partie
            files_writte << root;

            // Fermeture du fichier
            files_writte.close();

            cout << "--> Fin de l'enregistrement dans le fichier <--" << endl;
          }
          else{
            cerr << "Impossible d'ouvrir le fichier des commandes enregistrées pour l'ecriture" << endl;
          }

      }
    
    }
  }
