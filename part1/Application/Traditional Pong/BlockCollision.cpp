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

#include "BlockCollision.h"
#include "Hud.h"

// Constructor & Deconstructor
BlockCollision::BlockCollision()
{
	clip.grab("data/block.wav");
	clip.vol(50);
}

BlockCollision::~BlockCollision()
{
}

// this function gets the new angle for the ball
int BlockCollision::getNewAngle(int distance, int angle)
{
	int newAngle = 0;

	if(distance != 0) 
	{
		newAngle = (asin((float)distance/125)) * 180.0 / 3.14159265;
	}

	return(angle+newAngle);
}

// Event handler here we program what is to happen after the event is triggered
void BlockCollision::onActivated(void * data)
{
	// First we get the collision data
	CollisionData * info = static_cast<CollisionData *>(data);
	// then we get the ball from the collision data
	Ball * ball = static_cast<Ball *>(info->one); 
	// and then its behaviour
	BallBehaviour * bv = ball->getBehaviour();

	// we get the collision area
	SDL_Rect pos2 = info->area2;
	SDL_Rect pos1 = info->area1;

	// calculate the center
	int dfc = (pos2.y + (pos2.h/2)) - (pos1.y + (pos1.h/2));

	// then correctly calculate the new direction for the ball
	if(pos2.x == 50) 
	{
		bv->setup(getNewAngle(dfc, 90), 20, 20);
	}
	else if(pos2.x == 1870) 
	{
		bv->setup(getNewAngle(dfc, 270), 20, -20);
	}

	// and play the pong sound to indicate a hit
	clip.play(0);
}
