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

#include "BallBehaviour.h"
#include "Ball.h"

// Constructor & Deconstructor
BallBehaviour::BallBehaviour(Ball * ptr, Texture * t)
	: startDirection(-90), obj(ptr), spr(t),
	  origin(ptr->getPosition())
{
}

BallBehaviour::~BallBehaviour()
{
}

// returns the direction of the ball
int BallBehaviour::getDirection()
{
	return direction;
}

// sets teh direction of the ball
void BallBehaviour::setDirection(int i) 
{
	direction = i;
}

// resets 
void BallBehaviour::reset()
{
	SDL_Rect ori = origin[0];

	spr->setPosition(ori.x, ori.y, ori.w, ori.h);
	spr->setAngle(startDirection *= -1);

	direction = spr->getAngle();
}

void BallBehaviour::setup(int d, int x, int y)
{	
	direction = d;
	speedX = x;
	speedY = y;
}

void BallBehaviour::negateX()
{
	speedX *= -1;
}

void BallBehaviour::negateY()
{
	speedY *= -1;
}

std::string BallBehaviour::getPositionAsString()
{
	std::vector<SDL_Rect>& position = obj->getPosition();
	std::string strPosition = "B:";

	strPosition += to_string(position[0].x);
	strPosition += ":";
	strPosition += to_string(position[0].y);

	return strPosition;
}

void BallBehaviour::onAction()
{
	std::vector<SDL_Rect>& position = obj->getPosition();

	position[0].x += (int)(sin(direction * 3.14159265 / 180.0) * speedX);
	position[0].y += (int)(cos(direction * 3.14159265 / 180.0) * speedY);

	spr->setPosition(position[0].x, position[0].y, position[0].w, position[0].h);
}
