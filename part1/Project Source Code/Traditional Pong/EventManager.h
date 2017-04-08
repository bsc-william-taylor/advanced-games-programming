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

#pragma once

#include "CommonHeader.h"
#include "IListener.h"
#include "IHandler.h"

// a singleton class responsible for managing even listeners and handlers
class EventManager
{
private:
	// a list of event listeners
	std::vector<IListener *> events;
	// a static pointer to the one and only instance
	static EventManager * instance;
public:
	// Deconstructor
	~EventManager();

	// static get function to aquire the only instance
	static EventManager * get();

	// push a new listener into the list
	void PushEventEntry(IListener *);
	// perform listener checks to see if an event should be triggered
	void PerformChecks();
private:
	// private constructor as this is a singleton
	EventManager();
};
