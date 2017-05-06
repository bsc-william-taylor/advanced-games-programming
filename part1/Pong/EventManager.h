
#pragma once

#include "MajorInclude.h"
#include "IListener.h"
#include "IHandler.h"

class EventManager
{
	std::vector<IListener *> events;
	static EventManager * instance;
public:
    EventManager();
	~EventManager();

	static EventManager * get();

	void pushEventEntry(IListener *);
	void performChecks();
};
