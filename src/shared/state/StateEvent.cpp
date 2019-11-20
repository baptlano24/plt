#include "StateEvent.h"

using namespace state;

StateEvent::StateEvent(StateEventID id): id(id){}

void StateEvent::setID(StateEventID id){
	this->id = id;
}

StateEventID& StateEvent::getID(){
	StateEventID& refID = this->id;
	return refID;
}
