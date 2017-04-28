/**
 * 
 * Copyright (c) 2014 : William Taylor : wi11berto@yahoo.co.uk
 *  
 * This software is provided 'as-is', without any 
 * express or implied warranty. In no event will 
 * the authors be held liable for any damages 
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose, 
 * including commercial applications, and to alter it and redistribute 
 * it freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; 
 *    you must not claim that you wrote the original software. 
 *    If you use this software in a product, an acknowledgment 
 *    in the product documentation would be appreciated but 
 *    is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, 
 *    and must not be misrepresented as being the original software.
 *  
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "EventManager.h"

// init the static instance of the object
EventManager * EventManager::instance = NULL;

// Constructor & Deconstructor
EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

// returns the one and only singleton instance
EventManager * EventManager::get() 
{
	// if the instance has not been created
	if(instance == NULL) 
	{
		// create a instance of the class
		instance = new EventManager();
	} 
	
	// and return it to the user
	return instance;
}

// push a event listener to the event list
void EventManager::PushEventEntry(IListener * listeners)
{
	// if listener is a valid pointer
	if(listeners != NULL)
	{
		events.push_back(listeners);
	}
	else
	{
		// else throw an exception
		throw Error(GAME, "NULL listener is trying to be inserted into list", WILLIAM);
	}
}

// calls on all listeners to check if events should be created
void EventManager::PerformChecks()
{
	for(unsigned i = 0; i < events.size(); i++) 
	{
		events[i]->onCheck();
	}
}
