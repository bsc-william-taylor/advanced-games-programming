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
#include "Texture.h"

std::vector<Texture::TextureEntry *> Texture::loaded_textures;
unsigned int Texture::reference_count = NULL;

// Constructor & Deconstructor
Texture::Texture()
	: angle(NULL)
{
	++reference_count;
}

Texture::~Texture()
{
	--reference_count;

	if (reference_count == 0)
	{
		for (auto&& tex : loaded_textures)
		{
			if (tex->surface != NULL)
			{
				SDL_FreeSurface(tex->surface);
				NULLIFY(tex->surface);
			}

			if (tex->texture != NULL)
			{
				SDL_DestroyTexture(tex->texture);
				NULLIFY(tex->texture);
			}
		}

		loaded_textures.clear();
	}
}

// This function will check if we have already loaded this texture before
SDL_Texture * Texture::checkForDuplicate(Renderer * renderer, std::string str)
{
	// iterate through the entry vector looking for the same filename
	for (unsigned i = 0; i < loaded_textures.size(); i++) 
	{
		// if found return to the user
		if (loaded_textures[i]->filename == str) 
		{
			return loaded_textures[i]->texture;
		}
	}

	// return NULL when it isnt found
	return NULL;
}

// creates the texture object with assistance from the renderer
void Texture::create(Renderer * renderer, std::string filename)
{
	// first check for a duplicate
	texture = checkForDuplicate(renderer, filename);

	// if we didnt find one we will load a new texture
	if (texture == NULL)
	{
		// create a new entry
		TextureEntry * entry = new TextureEntry();
		entry->surface = IMG_Load(filename.c_str());
		entry->filename = filename;

		// if we failed to load the surface
		if (entry->surface == NULL)
		{
			// throw an exception alerting the user to the file that failed to load
			throw Error(TEXTURE, "Couldnt create texture : " + filename, WILLIAM);
		}
		else
		{
			// if successful create the texture from the loaded surface
			entry->texture = SDL_CreateTextureFromSurface(
				renderer->get(),
				entry->surface
				);

			// then free the surface from memory
			SDL_FreeSurface(entry->surface);
			entry->surface = NULL;
			// then pack it into the list of texture entrs
			loaded_textures.push_back(entry);
			// then set this classes texture to equal the new entry
			texture = entry->texture;
		}
	}
}

// Sets the position for the user
void Texture::setPosition(int x, int y, int w, int h)
{
	// just set the position
	position.x = x;
	position.y = y;
	position.w = w;
	position.h = h;
}

// sets the angle
void Texture::setAngle(double a) 
{
	angle = a;
}

// returns the angle as a copy
double Texture::getAngle() 
{
	return angle;
}

// returns a reference to the position
SDL_Rect& Texture::getPosition() 
{
	return position;
}

// returns the raw texture object
SDL_Texture * Texture::get() 
{
	return texture;
}
