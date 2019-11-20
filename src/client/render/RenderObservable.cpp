#include "RenderObservable.h"
#include <iostream>

using namespace render;
using namespace engine;
using namespace std;

void RenderObservable::registerObserver (engine::IRenderObserver* observer){
	observers.push_back(observer);
}

void RenderObservable::notifyObservers (engine::RenderEvent& renderEvent){
	for(auto observer : observers){
		observer->playerRequest(renderEvent);
	}
}
