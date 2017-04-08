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

class Renderer;

class Texture
{
private:
	// a struct for each texture loaded by this class
	struct TextureEntry {
		SDL_Surface * surface;
		SDL_Texture * texture;
		std::string filename;
	};
private:
	// the current instances texture
	SDL_Texture * texture;
	// its position on the screen
	SDL_Rect position;
	// its rotation value
	double angle;
public:
	// Constructor & Deconstructor
	Texture();
	~Texture();

	// creates the texture with assistance from the renderer
	void create(Renderer * renderer, std::string filename);
	// sets the position of the object to be drawn
	void setPosition(int x, int y, int w, int h);
	// sets the angle the object should be drawn as
	void setAngle(double newAngle);
public:
	// gets a reference to the position
	SDL_Rect& getPosition();
	// returns the texture as a pointer
	SDL_Texture * get();
	// returns the angle of the drawn texture
	double getAngle();
private:
	// private function which helps deal with duplicate entrys
	SDL_Texture * checkForDuplicate(Renderer * renderer, std::string str);
	static std::vector<TextureEntry *> loaded_textures;
	static unsigned int reference_count;
};
