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

#include "ButtonListener.h"
#include "Texture.h"
#include "Label.h"

// a simple class for rendering a button on screen
class Button : public IClickable
{
private:
	// a pointer to the listener that checks for a click
	ButtonListener * clickListener;
	// the buttons texture object
	Texture * texture;
	// the position or area to render into
	SDL_Rect surface;
	// the buttons text object
	Label * label;
public:
	// Constructor & Deconstructor
	Button();
	~Button();

	// sets the position of the button
	void setPosition(int x, int y, int w, int h);
	// creates a label to be rendered inside the area
	void createL(std::string, std::string, int);
	// creates a texture to be rendered as the background for the button
	void createT(Renderer *, std::string);
	// a simple method which will then update the click listener
	void onEvent(SDL_Event *);
	// a set event handler so the user can decide what happens when the button is clicked
	void onClick(IHandler *);
public:
	// returns a reference to the buttons area
	SDL_Rect& getClickRegion();
	// returns a pointer to the texture
	Texture* getTexture();
	// returns a pointer to the label
	Label* getLabel();
};
