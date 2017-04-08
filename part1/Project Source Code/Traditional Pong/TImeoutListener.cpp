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

#include "TimeoutListener.h"

// Constructor & Deconstructor
TimeoutListener::TimeoutListener(IHandler * handler, int ms)
{
	// set variables and start the timer
	this->event = handler;
	ms_timeout = ms;
	timer.start();
	active = true;
}

TimeoutListener::~TimeoutListener()
{
	if (event)
	{
		SAFE_RELEASE(event);
	}
}

// Check to see if the set time has passed
void TimeoutListener::onCheck()
{
	// stop the timer
	timer.stop();

	// and if the timer is active and the time has eleapsed
	if(active && timer.elapsed(MS) >= ms_timeout)
	{
		// call the event, clear the timer
		event->onActivated(this);
		timer.clear();
		// and make the timer inactive
		active = false;
	}
}

void TimeoutListener::makeActive()
{
	reset();
}

void TimeoutListener::disable()
{
	active = false;
}

// This function just re activates the timer for reuse
void TimeoutListener::reset()
{
	active = true;
	timer.start();
}
