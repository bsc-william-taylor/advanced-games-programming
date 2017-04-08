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

#include "Framework.h"
#include "IHandler.h"
#include "ICollidable.h"
#include "IListener.h"

// A struct which contains data about a collision
struct CollisionData {
	// the id for the side of the objects that collided
	unsigned int INDEX_1, INDEX_2;
	// the area for the bounding boxes
	SDL_Rect area1, area2;
	// a pointer to colliable object1
	ICollidable * one;
	// a pointer to colliable object2
	ICollidable * two;
};

// This class checks for a collision between 2 objects
class CollisionListener : public IListener
{
private:
	// a pointer to collidable object 1
	ICollidable * collidable1;
	// a pointer to collidable object 2
	ICollidable * collodable2;
	// the event to be called once triggered
	IHandler * event;
	// information about the collision 
	CollisionData * data;
public:
	// Constructor & Deconstructor
	CollisionListener();
	~CollisionListener();

	// Implemented all listener virtual functions
	void pushObjects(ICollidable *, ICollidable *, IHandler *);
	void onCheck();
};

// simple typdef because Collision is more readable in the game code
typedef CollisionListener Collision;
