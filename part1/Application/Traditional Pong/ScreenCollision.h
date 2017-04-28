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

#include "CollisionListener.h"
#include "ScreenCollision.h"
#include "Framework.h"
#include "Player.h"
#include "Ball.h"

#define BALL_RESET_DELAY 1500
#define POINTS_TO_WIN 10

class ScreenCollision : public IHandler
{
private:
	// The stats file to update when the ball bounces
	StatisticsFile * stats;
	// a pointer to the ball object in the scene
	Ball * ball;
	// a bool to stop the event triggering over and over again
	bool triggered;
public:
	// Constructor & Deconstructor
	ScreenCollision(SceneManager * mgr, StatisticsFile * f);
	~ScreenCollision();
	// Handler function for when the event is triggered
	void onActivated(void *);
	// a simple reset function
	void restart();
private:
	TimeoutListener timeoutListener;
	SceneManager * mgr;
	Music clip;
};
