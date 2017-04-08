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

#include "Label.h"

std::vector<FontEntry *> Label::fonts;
unsigned int Label::reference_count = 0;

// Constructor & Deconstructor
Label::Label()
	: surface(NULL),
	  text(" ")
{
	colour = { 255, 
		255, 
		255 
	};

	reference_count++;
}

Label::~Label()
{
	reference_count--;

	// once this is the final instance delete all fonts stored
	if (reference_count == NULL)
	{
		// go through the font list
		for (auto&& font : fonts)
		{
			// and if the font is still active
			if (font->font)
			{
				// free it from memory
				TTF_CloseFont(font->font);
				NULLIFY(font->font);
			}
		}
	}
}

// Sets the position of the label
void Label::setPosition(int x, int y, Alignment e)
{
	// set the position with a std::initializer_list
	position = { x, y,
		surface->w,
		surface->h
	};

	// calculate the new position based on the alignment
	switch (e)
	{
		// on center alignment, center the text at the position
		case CENTER:
		{
			position.x -= surface->w/2;
			position.y -= surface->h/2;
			break;
		}
		
		// on left alignment draw the text to the left of the point
		case LEFT:
		{
			position.x -= surface->w/2;
			break;
		}
		
		// else break
		default:
			break;
	}
}

// returns the text as a c style string
const char * Label::getText()
{
	return text;
}

// return the angle
double Label::getAngle()
{
	return 0.0F;
}

// return a reference to the position struct
SDL_Rect& Label::getPosition()
{
	return position;
}

// returns a raw pointer to the actual surface
SDL_Surface * Label::get() 
{
	return surface;
}

// sets the colour of the text to be rendered
void Label::setColour(SDL_Color colour)
{
	this->colour = colour;
}

void Label::create(std::string fontFile, std::string text, int sz)
{
	// set the text for the label
	this->text = text.c_str();

	// if the surface has already been loaded
	if (surface)
	{
		// free it
		SDL_FreeSurface(surface);
	} 

	// check to see if we have already loaded this font
	TTF_Font * font = checkForDuplicates(fontFile, sz);

	// if we havent
	if (font == NULL)
	{
		// we will create a new font
		FontEntry * returnFont = new FontEntry();
		returnFont->font = TTF_OpenFont(fontFile.c_str(), sz);
		returnFont->filename = fontFile;
		returnFont->sz = sz;

		// add it to the list of fonts
		fonts.push_back(returnFont);
		// and set the font to the newly created font
		font = (returnFont->font);
	}

	// render the text into a surface
	surface = TTF_RenderText_Blended(font, text.c_str(), colour);

	// then set a initial position
	position.x = NULL;
	position.y = NULL;
	position.w = surface->w;
	position.h = surface->h;
}

// checks to see if we have already loaded the font before
TTF_Font * Label::checkForDuplicates(std::string str, unsigned int fsz)
{
	// iterate through the vector looking for the font
	for (unsigned int i = 0; i < fonts.size(); i++) 
	{
		// if we find it
		if (fonts[i]->filename == str && fonts[i]->sz == fsz) 
		{
			// return the font to be used by the class
			return fonts[i]->font;
		}
	}

	// else return NULL to indicate failure
	return NULL;
}