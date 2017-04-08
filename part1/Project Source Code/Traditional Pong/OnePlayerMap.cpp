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


#include "Scenes.h"
#include "OnePlayerMap.h"
#include "AiBehaviour.h"

OnePlayerMap::OnePlayerMap(Bank * bank)
{
	this->bank = bank;
}

OnePlayerMap::~OnePlayerMap()
{
	SAFE_RELEASE(ball);
}

void OnePlayerMap::onRender(Renderer& renderer)
{
	renderer.renderTexture(&background);
	player1.render();
	player2.render();
	ball->render();

	hud.render(renderer);
}

void OnePlayerMap::onLoad(SceneManager& mgr, Renderer& renderer)
{
	background.create(&renderer, "data/map.png");
	background.setPosition(0, 0, 1920, 1080);
	
	ball = new Ball(&renderer, bank);
	hud.create(renderer);

	player1.load(0, renderer);
	player1.setBehaviour(new AiBehaviour(ball));

	player2.load(1, renderer);
	player2.setBehaviour(new PlayerBehaviour(15, true));

	ball->setDirectionSpeed(90, 20, -20);
	ball->create(&mgr, &player1, &player2);
	click = bank->pop_item<Music>("mouse_click_music");
}

void OnePlayerMap::onUpdate(SceneManager& scenes, Renderer&)
{
	player1.update();
	player2.update();
	ball->update();
	hud.update();
}

void OnePlayerMap::onEnter() 
{
	player1.update();
	player2.update();
	ball->reset();
	ball->showBall();
	hud.enter();
}

void OnePlayerMap::onEvent(SceneManager& scenes, SDL_Event * e)
{
	if(e->key.type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
	{
		scenes.setScene(MENU);
	}

	player1.event(*e);
	player2.event(*e);
}
