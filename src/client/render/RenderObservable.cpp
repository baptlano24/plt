#include "RenderObservable.h"
#include <iostream>
#include <thread>

using namespace render;
using namespace engine;
using namespace std;

void RenderObservable::registerObserver (engine::IRenderObserver* observer){
	observers.push_back(observer);
}

void RenderObservable::threadHandleOrder(engine::IRenderObserver* observer, engine::Move move){
	observer->handleOrder(move);
}

void RenderObservable::notifyObservers (Move move){
	for(auto observer : observers){
		observer->handleOrder(move);
		//threadHandleOrder(observer,move);
		//std::thread threadEngine(RenderObservable::threadHandleOrder,observer,move);
	}
}
