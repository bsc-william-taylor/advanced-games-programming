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

// The types of label alignment
enum Alignment {
	CENTER, LEFT, RIGHT
};

// each entry that we should track for duplicates
struct FontEntry {
	std::string filename;
	TTF_Font * font;
	unsigned sz;
};

// a class for renderable text
class Label
{
private:
	// the texts surface
	SDL_Surface * surface;
	// the colour of the text
	SDL_Color colour;
	// the position to be drawn
	SDL_Rect position;
	// the text to be loaded into the surface
	const char * text;
public:
	// Constructor & Deconstructor
	Label();
	~Label();

	// this function sets the position and alignment of the text
	void setPosition(int x, int y, Alignment);
	// this function creates the label to be drawn on screen
	void create(std::string, std::string, int);
	// this function sets the colour of the text
	void setColour(SDL_Color colour);
	// this function returns the text as a c style stirng
	const char * getText();
	// returns the raw SDL_Surface class
	SDL_Surface * get();
	// returns a reference to the position
	SDL_Rect& getPosition();
	// returns the angle of the label
	double getAngle();
private:
	//some functions and variables to deal with duplicates
	TTF_Font * checkForDuplicates(std::string str, unsigned);
	static std::vector<FontEntry *> fonts;
	static unsigned int reference_count;
};
