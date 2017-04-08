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

#include "ButtonListener.h"

// Constructor & Deconstructor
ButtonListener::ButtonListener()
	: event(NULL)
{
}

ButtonListener::~ButtonListener()
{
}

// Sets the objects that the listener will listen to and call once the button is clicked
void ButtonListener::pushObjects(IClickable * c, IHandler * e)
{
	object = c;
	event = e;
}

// When a SDL event is sent to the listener
void ButtonListener::onEvent(SDL_Event * eventData)
{
	// we check the state of the moused if the user has clicked on the screen
	if(eventData->button.state == SDL_PRESSED && eventData->button.button == SDL_BUTTON_LEFT)
	{
		// aquire buttons region
		SDL_Rect& pos = object->getClickRegion();

		// aquire the mouse x and y positions
		int mx = eventData->motion.x;
		int my = eventData->motion.y;

		// and if they click inside the buttons region
		if(mx >= pos.x && mx <= pos.x+pos.w && my >= pos.y && my <= pos.y+pos.h)
		{	
			// call the event handler to handle the evet
			event->onActivated(object);
		}
	}
}

void ButtonListener::onCheck()
{	
}
