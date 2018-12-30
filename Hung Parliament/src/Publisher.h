#pragma once
#include "stdafx.h"
#include "Listener.h"

class Publisher
{
protected:
	std::list<Listener*> listeners_;
public:
	Publisher() {}

	void addListener(Listener *newListener) {
		listeners_.push_back(newListener);
	}

	virtual void notifyListeners(Event &e) {

		for (std::list<Listener*>::iterator it = listeners_.begin(); it != listeners_.end(); ++it) {
			(*it)->handleEvent(e);
		}
	}

	virtual ~Publisher() {};
};

