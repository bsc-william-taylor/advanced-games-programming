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

#include "Hud.h"

int Display::player1 = 0;
int Display::player2 = 0;

Display::Display()
{
}

Display::~Display()
{
}

void Display::render(Renderer& renderer)
{
	renderer.renderLabel(&playerScore_1);
	renderer.renderLabel(&playerScore_2);
}

void Display::create(Renderer& renderer)
{
	playerScore_1.create(font, to_string(player1), 200);
	playerScore_2.create(font, to_string(player2), 200);

	playerScore_1.setPosition(1920/2, 0, LEFT);
	playerScore_2.setPosition(1920/2, 0, RIGHT);
}

void Display::update()
{
	playerScore_1.create(font, to_string(player1), 200);
	playerScore_2.create(font, to_string(player2), 200);

	playerScore_1.setPosition(1920/2 - 115, 100, LEFT);
	playerScore_2.setPosition(1920/2 + 100, 100, RIGHT);
}

void Display::enter()
{
	player1 = NULL;
	player2 = NULL;
}
