#pragma once
#include "stdafx.h"
#include <queue>
#include "Event.h"


class Listener
{
	std::queue<Event> events_;
public:
	Listener() {}

	virtual void handleEvent(Event &newEvent) {}

	virtual ~Listener() {};
};

