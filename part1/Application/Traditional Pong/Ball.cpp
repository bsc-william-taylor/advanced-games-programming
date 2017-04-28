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

#include "ScreenCollision.h"
#include "Ball.h"
#include "Screen.h"

Ball::Ball(Renderer * r, Bank * b)
{
	position.resize(1);
	renderer = r;
	show = false;
	bank = b;

	behaviour = new BallBehaviour(this, &sprite);
}

Ball::~Ball()
{
	delete(behaviour);
	behaviour = NULL;
}

BallBehaviour * Ball::getBehaviour()
{
	return(behaviour);
}

std::vector<SDL_Rect>& Ball::getPosition()
{
	return(position);
}

void Ball::setDirectionSpeed(int d, int x, int y)
{
	behaviour->setup(d, x, y);
}

SDL_Rect& Ball::getClickRegion()
{
	return(sprite.getPosition());
}

void Ball::update()
{
	if (show) {
		actor.UpdateBehaviours();
	}
}

void Ball::setPosition(int x, int y)
{
	position[0].x = x;
	position[0].y = y;
}

void Ball::create(SceneManager * mgr, Player * player1, Player * player2)
{
	sprite.create(renderer, "data/bar.png");
	sprite.setPosition(935, 521, 50, 50);

	actor.PushBehaviour(behaviour);

	listener.pushObjects(this, &screen, new ScreenCollision(mgr, bank->pop_item<StatisticsFile>("save_file")));
	player1_Collision.pushObjects(this, player1, new BlockCollision());
	player2_Collision.pushObjects(this, player2, new BlockCollision());

	EventManager::get()->PushEventEntry(&player1_Collision);
	EventManager::get()->PushEventEntry(&player2_Collision);
	EventManager::get()->PushEventEntry(&listener);

	position[0] = sprite.getPosition();
}

void Ball::hideBall()
{
	show = false;
}

void Ball::showBall()
{
	show = true;
}

void Ball::reset()
{
	sprite.setPosition(935, 521, 50, 50);
	position[0] = sprite.getPosition();
	behaviour->reset();
}

void Ball::render()
{
	if (show) {
		renderer->renderTexture(&sprite);
	}
}
