#include "CommandsService.h"
#include "ServiceException.h"

#include <iostream>
using namespace server;
using namespace std;

CommandsService::CommandsService(engine::Engine &engine) : AbstractService("/command"), engine(engine)
{
    commands["length"] = 0;
    commands["commands"][0] = "";
    commandsHistoric["length"] = 0;
    commandsHistoric["commands"][0] = "";
}

HttpStatus CommandsService::get(Json::Value &out, int id)
{
    // only new commands
    out = commands;

    // for each get , reinitialize the dynamic list of commands
    commands["length"] = 0;
    commands["commands"] = Json::Value(Json::arrayValue);

    return HttpStatus::OK;
}

HttpStatus CommandsService::post(Json::Value &out, Json::Value &in)
{
    commands["commands"][commands["length"].asUInt()] = in;
    commands["length"] = commands["length"].asUInt() + 1;

    // add also to the historic
    commandsHistoric["commands"][commandsHistoric["length"].asUInt()] = in;
    commandsHistoric["length"] = commandsHistoric["length"].asUInt() + 1;

    return HttpStatus::NO_CONTENT;
}

Json::Value CommandsService::getCommandsHistoric(){
    return commandsHistoric;
}
