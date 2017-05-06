
#include "EventManager.h"

EventManager * EventManager::instance = NULL;

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

EventManager * EventManager::get() 
{
	if(instance == NULL) 
	{
		instance = new EventManager();
	} 
	
	return instance;
}

void EventManager::pushEventEntry(IListener * listeners)
{
	if(listeners != NULL)
	{
		events.push_back(listeners);
	}
	else
	{
		throw Error(GAME, "NULL listener is trying to be inserted into list", WILLIAM);
	}
}

void EventManager::performChecks()
{
	for(unsigned i = 0; i < events.size(); i++) 
	{
		events[i]->onCheck();
	}
}
