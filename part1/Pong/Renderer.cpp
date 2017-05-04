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

#include "Renderer.h"

// Constructor & Deconstructor
Renderer::Renderer()
	: renderer(NULL)
{
}

Renderer::~Renderer()
{
	// if this renderer was actually created
	if(renderer)
	{
		// destroy the renderer
		SDL_DestroyRenderer(renderer);
	}
}

// renderers a label on the screen for the user
void Renderer::renderLabel(Label * str)
{
	// get the labels surface
	SDL_Surface * surface = str->get();

	// providing it has one
	if(surface != NULL)
	{
		// create a texture to render from the surface
		SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface); 
		
		// then copy it onto the screen
		SDL_RenderCopyEx(renderer, texture, 
			NULL, &str->getPosition(),
			str->getAngle(), NULL, 
			SDL_FLIP_NONE
		);

		// then destroy the temporary texture
		SDL_DestroyTexture(texture);
	}
}

// clears the windows buffer and scales the application for the screen size
void Renderer::clear(Window * window)
{
	// clear the renderers buffer
	SDL_RenderClear(renderer);

	int w = 0;
	int h = 0;	
	 
	// then get the windows size
	SDL_GetWindowSize(window->getWindow(), &w, &h);
	// and set the scale value for the renderer
	SDL_RenderSetScale(renderer, (float)w/1920, (float)h/1080);
}

// renders a button onto the screen
void Renderer::renderButton(Button * button)
{
	// get the texture of the button & the label of the button
	Texture * texture = button->getTexture();
	Label * string = button->getLabel();

	// if the button has a texture
	if(texture != NULL) 
	{
		// render the texture
		renderTexture(texture);
	}

	// if the button has a label
	if(string != NULL) 
	{
		// render the label
		renderLabel(string);
	}
}

// returns a direct pointer to the SDL_renderer object
SDL_Renderer * Renderer::get()
{
	return renderer;
}

void Renderer::renderTexture(Texture * texture)
{
	// if the texture has a usable texture to renderer
	if (texture->get() != NULL)
	{
		// copy it onto the screen
		SDL_RenderCopyEx(renderer, texture->get(),
			NULL, &texture->getPosition(),
			texture->getAngle(),
			NULL, SDL_FLIP_NONE
		);
	}
}

void Renderer::makeSimpleRenderer(Window * window)
{
	// providing we havent created a renderer before
	if (renderer == NULL)
	{
		// create a hardware accelerate renderer
		renderer = SDL_CreateRenderer(window->getWindow(),
			-1, SDL_RENDERER_ACCELERATED |
			SDL_RENDERER_PRESENTVSYNC
			);

		// if we didnt succeed
		if (renderer == NULL)
		{
			// throw an exception
			throw Error(RENDERER, "Couldnt create renderer a simple renderer", WILLIAM);
		}
		else
		{
			// else set some quality hints however we dont really care if these are ignored
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
			SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
		}
	}
	else
	{
		// if we are trying to create the renderer again throw an excfeption
		throw Error(RENDERER, "You cant recreate the renderer", WILLIAM);
	}
}

// swaps the windows buffer
void Renderer::swap()
{
	SDL_RenderPresent(renderer);
}
