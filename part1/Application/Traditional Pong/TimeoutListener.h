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
#include "highPrecisionTimer.h"
#include "ICollidable.h"
#include "IListener.h"

// a class that calls a even after a set amount of MS
class TimeoutListener : public IListener
{
private:
	// the timeout timer
	HighPrecisionTimer timer;
	// the amount of time till we trigger the event
	unsigned int ms_timeout;
	// the event to trigger
	IHandler * event;
	// is the timeout active
	bool active;
public:
	// Constructor & Deconstructor
	TimeoutListener(IHandler * handler, int ms);
	~TimeoutListener();

	void makeActive();
	void disable();

	// Implemented IListener virtual functions
	void onCheck();
	void reset();
};
