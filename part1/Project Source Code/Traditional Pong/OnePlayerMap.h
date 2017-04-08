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

#include "Framework.h"
#include "Resources.h"
#include "Ball.h"
#include "Player.h"
#include "Hud.h"

class OnePlayerMap : public Scene
{
private:
	Texture background;
	Player player2;
	Player player1;
	Display hud;
	Ball* ball;
public:
	OnePlayerMap(Bank *);
	~OnePlayerMap();

	void onEvent(SceneManager&, SDL_Event *);
	void onUpdate(SceneManager&, Renderer&);
	void onLoad(SceneManager&, Renderer&);
	void onRender(Renderer&);
	void onEnter();
private:
	Music * click;
	Bank * bank;
};
