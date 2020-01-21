#include "GameService.h"
#include "ServiceException.h"

using namespace server;

GameService::GameService (Game& game) : AbstractService("/game"), game(game) {

}

HttpStatus GameService::get (Json::Value& out, int id) {
    if(id == 1){
        bool can = 1;
        for(auto& p : game.getPlayers()){
            if(p.second->free == true) {
                can = 0;
                break;
            }
        }
        out["canStart"] = can;
    }
    else {
        out["status"] = game.getStatus(); // 1 => CREATING, 2 => RUNNING
    }
    
    return HttpStatus::OK;
}
