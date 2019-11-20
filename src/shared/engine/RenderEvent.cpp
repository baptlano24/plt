#include "RenderEvent.h"

using namespace engine;

RenderEvent::RenderEvent(RenderEventID id):id(id){}

void RenderEvent::setID(RenderEventID id){
	this->id = id;
}

RenderEventID& RenderEvent::getID(){
	RenderEventID& refID = this->id;
	return refID;
}
