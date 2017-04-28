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

#include "SceneManager.h"

// Constructor & Deconstructor
SceneManager::SceneManager() 
	: index(NULL)
{
}

SceneManager::~SceneManager() 
{
	// delete all scenes at the end
	for (auto&& scene : scenes) 
	{
		delete scene;
	}
}

// get a specific scene
Scene * SceneManager::getScene(unsigned int ID)
{
	return scenes[ID];
}

// prepares all scenes that have been inseted into the vector
void SceneManager::prepareScenes(Renderer& renderer) 
{
	for (auto&& scene : scenes)
	{
		// just call the onLoad scene function
		scene->onLoad(*this, renderer);
	}
}

// adds a list of scenes to the managers list
void SceneManager::putScenes(std::initializer_list<Scene *> game_scenes)
{
	// iterate through the initializer list adding each valid pointer to the scene list
	for (auto&& s : game_scenes) 
	{
		if (s != NULL) 
		{
			scenes.push_back(s);
		}
	}
}

// sets the  current active scene
void SceneManager::setScene(unsigned ID)
{
	// if we havent loaded any scenes yet
	if (scenes.empty()) 
	{
		// just set the index variable
		index = ID;
	} 
	else 
	{
		// otherwise providing we dont breach the size of the array
		if (ID < scenes.size())
		{
			// call the exit method of the current scene
			scenes[index]->onExit();
			// call the enter method of the incoming scene
			scenes[ID]->onEnter();
			// and set the index variable
			index = ID;
		}
		else 
		{
			// if we are out of bounds in the vector throw an exception
			throw Error(GAME, "Invalid scene ID");
		}
	}
}

// returns a pointer to the current scene
Scene * SceneManager::getCurrent() 
{
	return scenes[index];
}
