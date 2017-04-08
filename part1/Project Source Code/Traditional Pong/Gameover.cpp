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

#include "Gameover.h"
#include "Scenes.h"

Gameover::Gameover(Bank * bank)
{
	this->bank = bank;
}

Gameover::~Gameover()
{
}

void Gameover::onRender(Renderer& renderer)
{
	renderer.renderTexture(&background);
	renderer.renderLabel(&title);
	renderer.renderLabel(&winner);
	renderer.renderLabel(&score1);
	renderer.renderLabel(&score2);
	renderer.renderButton(&exit);
}

void Gameover::onLoad(SceneManager&, Renderer& renderer)
{
	background.create(&renderer, "data/background.png");
	background.setPosition(0, 0, 1920, 1080);

	title.create(font, "Game Over", 150);
	title.setPosition(1920/2, 150, CENTER);

	exit.createL(font, "Back", 100);
	exit.setPosition(50, 0, 200, 200);
	exit.onClick(this);

	winner.create(font, " ", 75);
	winner.setPosition(1920/2, 500, CENTER);

	score2.create(font, " ", 175);
	score1.create(font, " ", 175);
	score2.setPosition(1670, 500, CENTER);
	score1.setPosition(250, 500, CENTER);

	click = bank->pop_item<Music>("mouse_click_music");
}

void Gameover::setString(const char * str)
{
	this->winnerString = str;
}

void Gameover::onActivated(void * data)
{
	Button * clickedButton = static_cast<Button *>(data);

	if(clickedButton == &exit)
	{
		sceneManager->setScene(MENU);
	}

	click->play(0);
}

void Gameover::onUpdate(SceneManager& scenes, Renderer&)
{
	std::string player1ScoreString = to_string(Display::player1);
	std::string player2ScoreString = to_string(Display::player2);

	sceneManager = &scenes;

	if(winner.getText() != winnerString || score1.getText() != player1ScoreString || score2.getText() != player2ScoreString)
	{
		score2.create(font, player2ScoreString, 175);
		score1.create(font, player1ScoreString, 175);
		winner.create(font, winnerString, 200);

		winner.setPosition(1920 / 2, 500, CENTER);
		score2.setPosition(1670, 500, CENTER);
		score1.setPosition(250, 500, CENTER);
	}
}

void Gameover::onEvent(SceneManager&, SDL_Event * e)
{
	exit.onEvent(e);
}
