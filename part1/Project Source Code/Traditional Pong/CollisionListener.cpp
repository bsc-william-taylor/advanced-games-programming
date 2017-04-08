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

#include "CollisionListener.h"

// Constructor & Deconstructor
CollisionListener::CollisionListener()
{
	data = new CollisionData();
	event = NULL;
}

CollisionListener::~CollisionListener()
{
	SAFE_RELEASE(data);
}

// Recieves and stores objects to track and the event to call on collision
void CollisionListener::pushObjects(ICollidable * c1, ICollidable * c2, IHandler * e)
{
	collidable1 = c1;
	collodable2 = c2;
	event = e;
}

// checks if a collision has taken place
void CollisionListener::onCheck()
{
	// if an event has been set
	if(event != NULL)
	{
		// get the list of positions
		std::vector<SDL_Rect>& obj1 = collidable1->getPosition();
		std::vector<SDL_Rect>& obj2 = collodable2->getPosition();

		// has the event been activated
		bool activated = false;

		// iterate through each side
		for(unsigned i = 0; i < obj1.size(); i++) 
		{
			bool breakLoop = false;
			SDL_Rect rect = obj1[i];

			// check with each side
			for(unsigned z = 0; z < obj2.size(); z++) 
			{
				SDL_Rect size = obj2[z];
				
				// if we detect a collision
				if(rect.x <= size.x + size.w && rect.x + rect.w >= size.x )
				{
					if(rect.y <= size.y + size.h && rect.y + rect.h >= size.y) 
					{
						// setup the collision data to be passed to the event function
						breakLoop = true;

						data->INDEX_1 = i;
						data->INDEX_2 = z;
						data->area1 = rect;
						data->area2 = size;
						break;
					}
				}
			}

			// should we break because a collision has already happened
			if(breakLoop) {

				activated = true;
				break;
			}
		}
		
		// once activated
		if(activated)
		{
			data->one = collidable1;
			data->two = collodable2;

			// call the event handler
			event->onActivated(data);
		}
	}
}
