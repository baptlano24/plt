#include "StateObservable.h"
#include <iostream>

using namespace state;
using namespace std;

void StateObservable::registerObserver (IStateObserver* observer){
	observers.push_back(observer);
}

void StateObservable::notifyObservers (StateEvent& stateEvent, State& state){
	for(auto observer : observers){
		observer->stateChanged(stateEvent, state);
	}
}
