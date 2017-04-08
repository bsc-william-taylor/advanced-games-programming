
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


#include "LocalAssetManager.h"

// Constructor & Decosntructor
LocalAssetManager::LocalAssetManager()
{
	modelFiles.reserve(45);
	textures.reserve(45);
	fonts.reserve(10);
}

LocalAssetManager::~LocalAssetManager()
{
	// here we just delete all the objects loaded
	for (auto& tex : textures)
		delete tex;
	for (auto& model : modelFiles)
		delete model;
	for (auto& font : fonts)
		delete font;
}

// looks for the texture object specified via the filename
TextureAsset * LocalAssetManager::getT(std::string filename)
{
	for (auto& tex : textures) 
		if (tex->getName() == filename)
			return tex;
	return NULL;
}

// looks for the model object specified via the filename
ModelAsset * LocalAssetManager::getM(std::string filename)
{
	for (auto& model : modelFiles) 
		if (model->getName() == filename)
			return model;
	return NULL;
}

// looks for the label object specified via the filename
FontAsset * LocalAssetManager::getL(std::string font, int sz, SDL_Color c)
{
	for (auto& label : fonts) 
		if (label->getName() == font) {
			label->openAtSize(sz);
			label->setColour(c);
			return label;
		}
	return NULL;
}

// grabs and loads all the files specified in the list and returns the number of assets loaded
unsigned int LocalAssetManager::grab(std::initializer_list<std::string> list)
{
	// get the vector size before inserting any new filenames & track the number of loaded assets
	unsigned int start = filenames.size();
	unsigned int loads = NULL;

	// insert the list filenames into the filenames vector
	filenames.insert(filenames.end(), list.begin(), list.end());
	
	// then iterate through the recently inserted filenames
	for (int i = start; i < filenames.size(); i++)
	{
		// get the file type
		std::string str = filenames[i].substr(filenames[i].length() - 4);
		
		// if it is a image format that is supported
		if (str == ".jpg" || str == ".png" || str == ".bmp") 
		{
			TextureAsset * texture = new TextureAsset(filenames[i].substr(0, filenames[i].length() - 4));
			texture->grabFromFile(filenames[i].c_str());
			textures.push_back(texture);
			++loads;
			continue;
		} 

		// if its a font file format that is supported
		if (str == ".ttf" || str == ".otf") 
		{
			FontAsset * font = new FontAsset(filenames[i].substr(0, filenames[i].length() - 4));
			font->grabFromFile(filenames[i].c_str());
			fonts.push_back(font);
			++loads;
			continue;
		} 
		
		// if its a model format that is supported
		if (str == ".3DS" || str == ".obj" || str == ".3ds" || str == ".md2" || str == ".md3")
		{
			ModelAsset  * model = new ModelAsset(filenames[i].substr(0, filenames[i].length() - 4));
			model->grabFromFile(filenames[i].c_str());
			modelFiles.push_back(model);
			++loads;
			continue;
		}
	}

	// return the number of loaded assets to the user so they know all files specified were loaded
	return(loads);
}
