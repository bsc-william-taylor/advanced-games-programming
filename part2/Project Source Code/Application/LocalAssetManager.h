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

#include "Framework.h"
#include "TextureAsset.h"
#include "FontAsset.h"
#include "ModelFile.h"

typedef SDL_Surface Texture;
typedef SDL_Surface Font;

// A class which loads assets for each application state
class LocalAssetManager
{
private:
	// a vector of all the textures loaded by the scene
	std::vector<TextureAsset*> textures;
	// a vector of all the models loaded by the scene
	std::vector<ModelAsset*> modelFiles;
	// a vector of all the fonts loaded by the scene
	std::vector<FontAsset*> fonts;
public:
	// Constructor & Deconstructor
	LocalAssetManager();
	~LocalAssetManager();
	
	// loads all the files given in the list and returns the number loaded
	unsigned int grab(std::initializer_list<std::string>);
	// returns a texture object via filename (without extension)
	TextureAsset * getT(std::string filename);
	// returns a model object via filename (without extension)
	ModelAsset * getM(std::string filename);
	// returns a model object via filename (without extension)
	FontAsset * getL(std::string font, int, SDL_Color);
private:
	// a list of all the filenames that were given
	std::vector<std::string> filenames;
};