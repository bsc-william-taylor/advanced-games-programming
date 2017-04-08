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

// The types of return types for timer functions
enum TimeType {
	SECONDS, MS, NS
};

// a timer class for getting time passed
class HighPrecisionTimer
{
private:
	// the current ticks
	unsigned int m_current;
	// the current ticks at start
	unsigned int m_start;
	// the current ticks at stop
	unsigned int m_stop;
	// the frequency of the processor
	unsigned int m_freq;
public:
	// Constructor & Deconstructor
	HighPrecisionTimer();
	~HighPrecisionTimer();

	// the time difference between start() and stop()
	float difference(TimeType);
	// get the current time elapsed
	float elapsed(TimeType);

	// startd the timer
	void start();
	// stopd the timer
	void stop();
	// resetd class to initial state
	void clear();

	// get the current ticks
	unsigned int current();
};
