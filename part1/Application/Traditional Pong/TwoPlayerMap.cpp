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
#include "TwoPlayerMap.h"

TwoPlayerMap::TwoPlayerMap(Bank * bank)
{
	this->bank = bank;
}

TwoPlayerMap::~TwoPlayerMap()
{
	SAFE_RELEASE(ball);
}

void TwoPlayerMap::onRender(Renderer& renderer)
{
	renderer.renderTexture(&background);
	player1.render();
	player2.render();
	ball->render();

	hud.render(renderer);
}

void TwoPlayerMap::onLoad(SceneManager& mgr, Renderer& renderer)
{
	background.create(&renderer, "data/map.png");
	background.setPosition(0, 0, 1920, 1080);
	hud.create(renderer);

	player1.load(PLAYER_ONE, renderer);
	player2.load(PLAYER_TWO, renderer);
	player1.setBehaviour(new PlayerBehaviour(15, false));
	player2.setBehaviour(new PlayerBehaviour(15, true));

	ball = new Ball(&renderer, bank);
	ball->setDirectionSpeed(90, 20, -20);
	ball->create(&mgr, &player1, &player2);

	click = bank->pop_item<Music>("mouse_click_music");
}

void TwoPlayerMap::onUpdate(SceneManager& scenes, Renderer&)
{
	player1.update();
	player2.update();
	ball->update();
	hud.update();
}

void TwoPlayerMap::onEnter() 
{
	player1.clear();
	player2.clear();
	ball->reset();
	hud.enter();
}

void TwoPlayerMap::onEvent(SceneManager& scenes, SDL_Event * e)
{
	if(e->key.type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
	{
		scenes.setScene(MENU);
	}

	player1.event(*e);
	player2.event(*e);
}
