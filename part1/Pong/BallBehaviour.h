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

class Ball;

// The behaviour or animation for the pong/ball
class BallBehaviour : public Behaviour
{
private:
	ActorPosition origin;
	Texture * spr;
	Ball * obj;
public:
	// Constructor & Deconstructor
	BallBehaviour(Ball *, Texture *);
	~BallBehaviour();

	//
	void setDirection(int i);
	//
	int getDirection();
	//
	std::string getPositionAsString();
	//
	void setup(int, int, int);
	void onAction();
	void negateX();
	void negateY();
	void reset();
private:
	// properties for the balls movement
	int startDirection;
	int direction;
	int speedX;
	int speedY;

};
