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

#include "Player.h"
#include "Music.h"
#include "Ball.h"

class Menu : public Scene, public IHandler
{
private:
	SceneManager * sceneManager;
	Texture background;
	Music * click;
	Bank * bank;
public:
	Menu(Bank *);
	~Menu();

	void onRender(Renderer& renderer);
	void onLoad(SceneManager&, Renderer& renderer);
	void onUpdate(SceneManager&, Renderer&);
	void onEvent(SceneManager&, SDL_Event *);
	void onActivated(void *);
private:
	Button multiplayer, stats, about, play1, play2, exit;
	Label version;
	Label title;
};
