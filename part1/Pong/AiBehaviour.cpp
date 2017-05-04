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

#include "AiBehaviour.h"
#include "Player.h"
#include "Ball.h"

// Constructor & Deconstructor
AiBehaviour::AiBehaviour(Ball * ball)
	: ball(ball)
{
}

AiBehaviour::~AiBehaviour()
{
}

// Handles when the behaviour needs to be updated
void AiBehaviour::onAction()
{
	// get the balls position
	SDL_Rect ballPosition = ball->getPosition()[0];
	// get the padles position
	SDL_Rect sprPosition = spr->getPosition();

	// calculate the distance to travel
	int distancey = 0;
	
	if(ballPosition.y > sprPosition.y+8) 
		distancey = 8;
	if(ballPosition.y < sprPosition.y-8) 
		distancey = -8;
	
	// increase the padles position by the distance providing it doesnt leave the screen by doing so
	SDL_Rect& position = spr->getPosition();
	if(position.y+position.h+distancey <= 1060 && position.y+distancey >= 20) 
	{
		spr->getPosition().y += distancey;
	}
}

// Handles when the behaviour is accepted by the Player object
void AiBehaviour::onAccept(void * obj) 
{
	// perform a cast and grab the players texture
	spr = static_cast<Player *>(obj)->getTexture();
}

// Should reset the padle but this hasnt been implemented
void AiBehaviour::reset()
{	
}
