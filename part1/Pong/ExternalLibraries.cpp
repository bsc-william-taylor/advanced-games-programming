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

#include "ExternalLibraries.h"

// Constructor & Deconstructor
ExternalLibraries::ExternalLibraries()
	: IMG_Params(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_JPG),
	  MIX_Params(MIX_INIT_OGG | MIX_INIT_MOD | MIX_INIT_MP3),
	  SDL_Params(SDL_INIT_EVERYTHING)
{
}

ExternalLibraries::~ExternalLibraries()
{
}

// inits and imports all required libraries
void ExternalLibraries::importLibraries()
{
	// if SDL init fails
	if(SDL_Init(SDL_Params) != NULL) 
	{
		// throw an exception
		throw Error(GAME, "Couldnt init SDL");
	}

	// if SDL_IMG init fails
	if(IMG_Init(IMG_Params) != IMG_Params) 
	{
		// throw an exception
		throw Error(GAME, "Couldnt init IMG");
	}

	// if SDL_TTF init fails
	if(TTF_Init() != NULL) 
	{
		// throw an exception
		throw Error(GAME, "Couldnt init TTF");
	}

	// if SDL_Mixer fails
	if(Mix_Init(MIX_Params) == NULL) 
	{
		// throw an exception
		throw Error(GAME, "Couldnt init Mixer");
	}

	// automatically try to open the default audio device
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2014) < NULL) 
	{
		/// on fail throw an error
		throw Error(GAME, "Error with grabbing audio device");
	}

	// if SDL_Init fails
	if (SDLNet_Init()) 
	{
		// throw an error
		throw Error(GAME, "Error with grabbing network device");
	}
}

// unloads all libraries that should of been imported
void ExternalLibraries::exportLibraries()
{
	// close all opened libraries
	Mix_CloseAudio();
	SDLNet_Quit();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
