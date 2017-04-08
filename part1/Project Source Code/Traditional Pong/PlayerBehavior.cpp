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

#include "PlayerBehavior.h"
#include "Player.h"

PlayerBehaviour::PlayerBehaviour(int s, bool r)
	: right(r), speed(s)
{
	reset();
}

PlayerBehaviour::~PlayerBehaviour()
{
}

void PlayerBehaviour::onAction()
{
	 if (keys[0] && right) move(spr, speed); 
	 if (keys[1] && right) move(spr, -speed); 
     if (keys[2] && !right) move(spr, -speed);  
     if (keys[3] && !right) move(spr, speed); 
}

void PlayerBehaviour::onEvent(SDL_Event& e)
{
	if (e.key.state == SDL_PRESSED)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_DOWN: keys[0] = true; break;
			case SDLK_UP: keys[1] = true; break;
			case SDLK_w: keys[2] = true; break;
			case SDLK_s: keys[3] = true; break;

			default:
				break;
		}
	}

	if (e.key.state == SDL_RELEASED)
	{
		switch (e.key.keysym.sym)
		{
			case SDLK_DOWN: keys[0] = false; break;
			case SDLK_UP: keys[1] = false; break;
			case SDLK_w: keys[2] = false; break;
			case SDLK_s: keys[3] = false; break;

			default:
				break;
		}
	}
}

void PlayerBehaviour::onAccept(void * obj) 
{
	spr = static_cast<Player *>(obj)->getTexture();
}

void PlayerBehaviour::reset()
{
	for (int i = 0; i < 4; i++)
	{
		keys[i] = false;
	}
}

void PlayerBehaviour::move(Texture * texture, int speed)
{
	SDL_Rect& position = texture->getPosition();
	
	if(position.y+position.h+speed <= 1060 && position.y+speed >= 20) 
	{
		texture->getPosition().y += speed;
	}
}
