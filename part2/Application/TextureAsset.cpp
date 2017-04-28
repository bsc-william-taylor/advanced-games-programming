
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


#include "TextureAsset.h"

// Constructor & Deconstructor
TextureAsset::TextureAsset(std::string n)
{
	textureSurface = NULL;
	name = n;
}

TextureAsset::~TextureAsset()
{
	if (textureSurface != NULL) {
		SDL_FreeSurface(textureSurface);
	}
}

// here we just load the image as a surface and throw an exception if something goes wrong
void TextureAsset::grabFromFile(const char * filename)
{
	// load the surface
	textureSurface = IMG_Load(filename);
	
	// if we failed throw an exception
	if (textureSurface == NULL) 
	{
		throw Error(FILE_IO, std::string(filename, " couldnt load a texture"));
	}
}

// returns the assets name
std::string TextureAsset::getName()
{
	return name;
}

// returns a pointer to the surface loaded
SDL_Surface * TextureAsset::getSurface()
{
	return textureSurface;
}

// returns a direct void * to pixels
void * TextureAsset::getPixels()
{
	return textureSurface->pixels;
}

// returns the amount of bpp for the texture
int TextureAsset::getBPP()
{
	return this->textureSurface->format->BytesPerPixel;
}

// returns the format of the texture
int TextureAsset::getMask()
{
	return this->textureSurface->format->Rmask;
}
// returns the width of the texture
int TextureAsset::getWidth()
{
	return textureSurface->w;
}

// returns the height of the texture
int TextureAsset::getHeight()
{
	return textureSurface->h;
}