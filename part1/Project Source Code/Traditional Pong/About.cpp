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

About::About(Bank * bank)
{
	this->bank = bank;
}

About::~About()
{
}

void About::onRender(Renderer& renderer)
{
	renderer.renderTexture(&background);
	renderer.renderLabel(&title);
	renderer.renderButton(&exit);
	renderer.renderLabel(&email);
	paragraph.render(renderer);
}

void About::onLoad(SceneManager&, Renderer& renderer)
{
	background.create(&renderer, "data/background.png");
	background.setPosition(0, 0, 1920, 1080);

	title.create(font, "Credits", 150);
	title.setPosition(1920/2, 150, CENTER);
		
	exit.createL(font, "Back", 100);
	exit.setPosition(50, 0, 200, 200);
	exit.onClick(this);

	paragraph.setPosition(1920/2, 300, CENTER);
	paragraph.setup(50, "data/about.xml", "about");

	email.create(font, "wi11berto@yahoo.co.uk", 30);
	email.setPosition(20, 1030, RIGHT);

	click = bank->pop_item<Music>("mouse_click_music");
}

void About::onActivated(void * data)
{
	Button * clickedButton = static_cast<Button *>(data);

	if(clickedButton == &exit)
	{
		sceneManager->setScene(MENU);
	}

	click->play(0);
}
	
void About::onUpdate(SceneManager& scenes, Renderer&)
{
	sceneManager = &scenes;
}

void About::onEvent(SceneManager& scenes, SDL_Event * e)
{
	if(e->key.type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
	{
		scenes.setScene(MENU);
	}

	exit.onEvent(e);
}
