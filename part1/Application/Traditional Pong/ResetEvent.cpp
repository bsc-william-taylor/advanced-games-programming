
#include "ResetEvent.h"
#include "ScreenCollision.h"

// Constructor & Deconstructor
Reset_Event::Reset_Event(ScreenCollision * e)
	: event(e)
{ 
}

Reset_Event::~Reset_Event()
{
}

void Reset_Event::onActivated(void * data)
{
	// we just take the screen collision event and tell it to restart
	event->restart();
}