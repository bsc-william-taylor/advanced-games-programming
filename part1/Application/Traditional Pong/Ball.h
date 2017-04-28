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
#include "BlockCollision.h"
#include "BallBehaviour.h"
#include "Resources.h"
#include "Framework.h"
#include "Player.h"

class Ball : public ICollidable
{
private:
	BallBehaviour* behaviour;
	ActorPosition position;
	Texture sprite;
	Screen screen;
	Actor actor;
	Bank * bank;
public:
	Ball(Renderer *, Bank *);
	~Ball();

	BallBehaviour* getBehaviour();
	ActorPosition& getPosition();
	SDL_Rect& getClickRegion();

	void create(SceneManager *, Player *, Player *);
	void setDirectionSpeed(int, int, int);
	void setPosition(int, int);
	void hideBall();
	void showBall();
	void update();
	void render();
	void reset();
private:
	Collision player1_Collision;
	Collision player2_Collision;
	Collision listener;
	Renderer * renderer;
private:
	bool show;
};
