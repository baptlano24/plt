#include <string.h>
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
#include <sys/types.h>
#include <microhttpd.h>
#include <sys/select.h>
#include "server.h"
#include "state.h"
#include "../client/render.h"
#include "engine.h"
#include "ai.h"

#define SOCKET_ERROR -1

using namespace server;
using namespace std;
using namespace state;
using namespace sf;
using namespace render;
using namespace engine;
using namespace ai;



int delai = 300000 ;
void recordheuristicVSheuristic();
void listen1();

class Request
{
public:
    struct MHD_PostProcessor *pp = nullptr;
    string data;
    ~Request()
    {
        if (pp)
            MHD_destroy_post_processor(pp);
    }
};


static int post_iterator(void *cls,
                         enum MHD_ValueKind kind,
                         const char *key,
                         const char *filename,
                         const char *content_type,
                         const char *transfer_encoding,
                         const char *data, uint64_t off, size_t size)
{
    return MHD_NO;
}

static int handler(void *cls,
             struct MHD_Connection *connection,
             const char *url,
             const char *method,
             const char *version,
             const char *upload_data, size_t *upload_data_size, void **ptr)
{
    Request *request = (Request *)*ptr;

    if (!request)
    {
        request = new Request();
        if (!request)
        {
            return MHD_NO;
        }
        *ptr = request;
        if (strcmp(method, MHD_HTTP_METHOD_POST) == 0 || strcmp(method, MHD_HTTP_METHOD_PUT) == 0)
        {
            request->pp = MHD_create_post_processor(connection, 1024, &post_iterator, request);
            if (!request->pp)
            {
                cerr << "Failed to setup post processor for " << url << endl;
                return MHD_NO;
            }
        }
        return MHD_YES;
    }

    if (strcmp(method, MHD_HTTP_METHOD_POST) == 0 || strcmp(method, MHD_HTTP_METHOD_PUT) == 0)
    {
        MHD_post_process(request->pp, upload_data, *upload_data_size);
        if (*upload_data_size != 0)
        {
            request->data = upload_data;
            *upload_data_size = 0;
            return MHD_YES;
        }
    }

    HttpStatus status;
    string response;
    try
    {
        ServicesManager *manager = (ServicesManager *)cls;
        status = manager->queryService(response, request->data, url, method);
    }
    catch (ServiceException &e)
    {
        status = e.status();
        response += "\n";
    }
    catch (exception &e)
    {
        status = HttpStatus::SERVER_ERROR;
        response = e.what();
        response += "\n";
    }
    catch (...)
    {
        status = HttpStatus::SERVER_ERROR;
        response = "Unknown exception\n";
    }

    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(response.size(), (void *)response.c_str(), MHD_RESPMEM_MUST_COPY);
    if (strcmp(method, MHD_HTTP_METHOD_GET) == 0)
    {
        MHD_add_response_header(mhd_response, "Content-Type", "application/json; charset=utf-8");
    }
    int ret = MHD_queue_response(connection, status, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

static void request_completed(void *cls, struct MHD_Connection *connection, void **con_cls, enum MHD_RequestTerminationCode toe)
{
    Request *request = (Request *)*con_cls;
    if (request)
    {
        delete request;
        *con_cls = nullptr;
    }
}


int main(int argc,char* argv[1]) {
  if(argc>=2 && string(argv[1])=="hello") {
    cout << "Hello world !" << endl;
  }
  else if (argc>=2 && string(argv[1])=="record") {
    recordheuristicVSheuristic();
  }
  else if (argc>=2 && string(argv[1])=="listen"){
    try {
        Game game;
        ServicesManager servicesManager;

        AbstractService* ptr_versionService(new VersionService());
        servicesManager.registerService(move(ptr_versionService));

        AbstractService* ptr_playerService(new PlayerService(ref(game)));
        servicesManager.registerService(move(ptr_playerService));

        AbstractService* ptr_gameService(new GameService(ref(game)));
        servicesManager.registerService(move(ptr_gameService));

        AbstractService* ptr_commandService(new CommandsService(game.getEngine()));
        servicesManager.registerService(move(ptr_commandService));

        struct MHD_Daemon *d;
        if (argc != 2)
        {
            printf("%s PORT\n", argv[0]);
            return 1;
        }

        d = MHD_start_daemon( // MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG | MHD_USE_POLL,
            MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
            // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG | MHD_USE_POLL,
            // MHD_USE_THREAD_PER_CONNECTION | MHD_USE_DEBUG,
            8080,
            NULL, NULL,
            &handler, (void *)&servicesManager,
            MHD_OPTION_NOTIFY_COMPLETED, request_completed, NULL,
            MHD_OPTION_END);

        if (d == NULL)
            return 1;
        cout << "server is listening in port 8080..." << endl << "press any button to stop the server" << endl;
        (void)getc(stdin);
        MHD_stop_daemon(d);
    }
    catch (exception &e)
    {
        cerr << "Exception: " << e.what() << endl;
    }
}

  }


void recordheuristicVSheuristic(){
    std::string files_order = "../res/replay.txt";
    std::ofstream files_writte(files_order, ios::out|ios::trunc);
    Engine engine;
    Engine* ptr_engine = &engine;
    sf::RenderWindow window(sf::VideoMode(1314,949), "Jungle War");
    sf::RenderWindow* ptr_window = &window;
    RenderLayer stateLayer(engine.getptrState(), ptr_window);
    RenderLayer* ptr_stateLayer = &stateLayer;
    HeuristicAI heuristicAI0(0);
    HeuristicAI heuristicAI1(1);
    engine.setEnableRecord(true);
    stateLayer.registerObserver(ptr_engine);
    engine.getState().registerObserver(ptr_stateLayer);
    stateLayer.draw(ptr_window);
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
      if(engine.getState().getTurn()> 12) {
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
          break;
      }

    }
  }
