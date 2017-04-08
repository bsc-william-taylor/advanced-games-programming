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

#include "CommonHeader.h"
#include "Texture.h"
#include "Button.h"
#include "Label.h"
#include "Window.h"

// a renderer which will render 2D drawables
class Renderer
{
private:
	// a reference to the raw renderer class
	SDL_Renderer * renderer;
public:
	// Constructor & Deconstructor
	Renderer();
	~Renderer();

	// makes the renderer for the window passed as a parameter
	void makeSimpleRenderer(Window *);
	// renders a texture on the screen
	void renderTexture(Texture *);
	// renders a button on the screen
	void renderButton(Button *);
	// renders a label on the screen
	void renderLabel(Label *);
	// clears the windows region/buffer
	void clear(Window *);
	// swaps the buffers bringing the drawn scene to the front
	void swap();
public:
	// a function to get the raw SDL renderer
	SDL_Renderer * get();
};
