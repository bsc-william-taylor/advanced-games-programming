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
#include "ICollidable.h"
#include "PlayerBehavior.h"
#include "Resources.h"
#include "Framework.h"
#include "Screen.h"

enum PLAYER_TYPE {
	PLAYER_ONE,
	PLAYER_TWO
};

class Player : public ICollidable
{
public:
	Player();
	~Player();

	ActorPosition& getPosition();
	Texture * getTexture();
	
	std::string getPositionAsString();
	void setBehaviour(Behaviour *);
	void setPosition(int, int);
	void load(int, Renderer&);
	void event(SDL_Event&);
	void render();
	void update();
	void clear();
private:
	ActorPosition positions;
	Texture sprites;
	Renderer * renderer;
	Actor * actor;
};
