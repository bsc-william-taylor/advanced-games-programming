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

#include "Button.h"

// Constructor & Deconstructor
Button::Button()
	: clickListener(new ButtonListener()),
	  texture(NULL),
	  label(NULL)
{
}

Button::~Button()
{
	// safely release objects
	SAFE_RELEASE(clickListener);
	SAFE_RELEASE(texture);
	SAFE_RELEASE(label);
}

// pushes a event handler to be alerted when the button is clicked by a mouse
void Button::onClick(IHandler * e)
{
	clickListener->pushObjects(this, e);
}


// returns a reference to the windows region
SDL_Rect& Button::getClickRegion()
{
	return surface;
}

// this function updates the listener with mouse input events
void Button::onEvent(SDL_Event * event)
{
	// check for a mouse click event
	clickListener->onEvent(event);
	clickListener->onCheck();
}

// sets the position of the button in 2D space
void Button::setPosition(int x, int y, int w, int h)
{
	surface = { x, y, w, h };

	// calculate the middle of the buttons area for text
	int mdx = x+(w/2);
	int mdy = y+(h/2);

	// if a label has been loaded
	if (label)
	{
		// set the position
		label->setPosition(mdx, mdy, CENTER);
	}
	
	// if a texture has been loaded
	if (texture)
	{
		// set the position
		texture->setPosition(x, y, w, h);
	}
}

// creates a label to be placed inside the buttons area
void Button::createL(std::string str, std::string str2, int sz)
{
	// if a label has already been loaded delete it
	if (label) SAFE_RELEASE(label);

	// load the new label for the button
	label = new Label();
	label->create(str, str2, sz);
}

// return a pointer to the buttons texture
Texture * Button::getTexture() 
{
	return texture;
}

// return a pointer to the buttons label
Label * Button::getLabel() 
{
	return label;
}

// creates a texture for the button
void Button::createT(Renderer * renderer, std::string filename)
{
	// if one has already been loaded releases the previous version
	if (texture) SAFE_RELEASE(texture);

	// then create the texture
	texture = new Texture();
	texture->create(renderer, filename);
}
