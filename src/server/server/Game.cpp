#include "Game.h"
#include <memory>
#include <map>
#include <vector>
#include <set>

using namespace server;
using namespace std;
using std::unique_ptr;
using std::map;
using std::vector;

Game::Game () : engine(){}

Player* Game::getPlayerById (int id){
    auto it = players.find(id);
    if (it == players.cend())
        return nullptr;
    return it->second;
};

GameStatus Game::getStatus() const {
    if(players.size() == 2) return RUNNING;
    return CREATING;
}

engine::Engine& Game::getEngine(){
    return engine;
}

const std::map<int, Player*>& Game::getPlayers() const {
    return players;
}

void Game::modifyPlayer (int id, Player* newData){
    players[id] = move(newData);
    if (id > baseId) baseId = id;
}

void Game::removePlayer (int id){
    auto it = players.find(id);
    if (it == players.end())
        return;
    players.erase(it);
}

int Game::addPlayer (Player* newPlayer){
    int id = baseId;
    players.insert(std::make_pair(id, std::move(newPlayer)));
    baseId += 1;
    return id;
}
