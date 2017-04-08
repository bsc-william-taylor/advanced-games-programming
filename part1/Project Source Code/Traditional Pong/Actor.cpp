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

#include "Actor.h"

// Constructor & Deconstructor
Actor::Actor()
{
	behaviours.reserve(BEHAVIOUR_RESERVE_SIZE);
}

Actor::~Actor()
{
}

// Pushes a new behaviour into the list
void Actor::PushBehaviour(Behaviour * ptr)
{
	// is the ptr is valid
	if(ptr != NULL) 
	{
		// push it into the list
		behaviours.push_back(ptr);
	}
	else
	{
		// otherwise throw an exception
		throw Error(GAME, "Entering null behaviour", WILLIAM);
	}
}

// Notifys all behaviour about SDL events
void Actor::NotifyBehaviours(SDL_Event& e)
{
	// pass the event reference to all behaviours
	for (auto&& behaviour : behaviours)
	{
		behaviour->onEvent(e);
	}
}

// Pops the last behaviour
void Actor::PopBehaviour(Behaviour * ptr)
{
	behaviours.pop_back();
}

// Updates all the behaviours
void Actor::UpdateBehaviours()
{
	for (auto&& behaviour : behaviours)
	{
		behaviour->onAction();
	}
}
