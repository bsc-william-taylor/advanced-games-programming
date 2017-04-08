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

#include "EventManager.h"
#include "Player.h"

Player::Player()
{
	actor = new Actor();
}

Player::~Player()
{

}

void Player::render()
{
	renderer->renderTexture(&sprites);
}

Texture * Player::getTexture()
{
	return &sprites;
}

void Player::setBehaviour(Behaviour * beh)
{
	beh->onAccept(this);
	actor->PushBehaviour(beh);
}

std::string Player::getPositionAsString()
{
	std::string str = "";

	str += to_string(sprites.getPosition().x);
	str += ":";
	str += to_string(sprites.getPosition().y);

	return str;
}

void Player::setPosition(int x, int y)
{
	sprites.setPosition(x, y, 20, 200);
	positions.clear();
	positions.push_back(sprites.getPosition());
}

ActorPosition& Player::getPosition()
{
	positions.clear();
	positions.push_back(sprites.getPosition());

	return(positions);
}

void Player::event(SDL_Event& e)
{
	actor->NotifyBehaviours(e);
}

void Player::clear()
{
	//keys.clear();
}


void Player::update()
{
	actor->UpdateBehaviours();
}

void Player::load(int i, Renderer& renderer)
{
	this->renderer = &renderer;

	SDL_Rect rect[2] = { 
		{ 50,   490,  20,  200 },
		{ 1870, 490,  20,  200 } 
	};

	sprites.create(this->renderer, "data/bar.png");
	sprites.setPosition(rect[i].x, rect[i].y, rect[i].w, rect[i].h); 
}
