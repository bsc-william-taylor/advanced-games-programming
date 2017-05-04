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
#include "Ball.h"

class Statistics : public Scene, public IHandler 
{
private:
	StatisticsData * statistics;
	SceneManager * sceneManager;
	Music * click;
	Bank * bank;
public:
	Statistics(Bank * bank);
	~Statistics();
	
	void onUpdate(SceneManager& sceneManager, Renderer& renderer);
	void onEvent(SceneManager& sceneManager, SDL_Event* sdl_event);
	void onLoad(SceneManager& sceneManager, Renderer& renderer);
	void onRender(Renderer& renderer);
	void onActivated(void * data);
private:
	Label timesPlayedTitle;
	Label timesPlayed;
	Label bounceTitle;
	Label bounces;
	Label title;

	Texture background;
	Button exit;
};
