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

#define BEHAVIOUR_RESERVE_SIZE 10

// A interface for actor behaviours
class Behaviour
{
public:
	virtual void onEvent(SDL_Event&) {}
	virtual void onAccept(void *) {}
	virtual void onAction() = 0;
	virtual ~Behaviour() {}
};

// a actor class which will manage a list of behaviours
class Actor
{
private:
	// the list of behaviours the object has
	std::vector<Behaviour *> behaviours;
public:
	// virtual deconstructor
	virtual ~Actor();
	Actor();

	// pushes a new behaviour into the list
	void PushBehaviour(Behaviour *);
	// removes a behaviour fromt the list
	void PopBehaviour(Behaviour *);
	// notifiys all behaviours about input events
	void NotifyBehaviours(SDL_Event&);
	// signals all behaviours to update the actors traits
	void UpdateBehaviours();
};
