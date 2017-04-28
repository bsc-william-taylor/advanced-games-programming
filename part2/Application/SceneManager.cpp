
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
SceneManager::SceneManager(Window * w) 
{
	// here we reserve some memory and set vars
	engineScenes.reserve(100);
	globalScene = NULL;
	current = NULL;
	window = w;
}

SceneManager::~SceneManager()
{	
}

// just sets the global scene for the application
void SceneManager::setGlobalScene(Scene * scene)
{
	globalScene = scene;
}

// here we accept a list of scenes and pack each one individually into the vector
void SceneManager::packSceneList(std::initializer_list<Scene *> scenes)
{
	for (auto& scene : scenes)
	{
		engineScenes.push_back(scene);
	}
}

// here we call both the global scene and active scenes render method
void SceneManager::renderScene()
{
	// make sure we actually have scenes first 
	if (!engineScenes.empty()) 
	{
		// then call the render function 
		engineScenes[current]->onRender();
	}

	// likewise for the global scene
	if (globalScene != NULL)
	{
		globalScene->onRender();
	}
}

// Here we handle SDL events and send them to active scenes
void SceneManager::handeEventScene(SDL_Event& e)
{
	// we automatically handle exit events
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
		SDL_Event exit;
		exit.type = SDL_QUIT;
		SDL_PushEvent(&exit);
	}

	// and we resize coordinates so the application is fully scalable
	if (e.type == SDL_MOUSEMOTION || e.button.button == SDL_BUTTON_LEFT)
	{
		int w = 0;
		int h = 0;

		// Get the windows size
		SDL_GetWindowSize(window->getWindow(), &w, &h);

		// here we resize the mouse x,y co ordinates to match a new window size
		e.motion.x *= ((float)1920 / w);
		e.motion.y *= ((float)1080 / h);
		e.motion.y = 1080 - e.motion.y;
	}

	// then alert both the global state and the current active state
	if (!engineScenes.empty())
	{
		engineScenes[current]->onGameEvent(e);
	}

	if (globalScene != NULL)
	{
		globalScene->onGameEvent(e);
	}
}

// here we just send an exit event to the event queue
void SceneManager::exit()
{
	SDL_Event exit;
	exit.type = SDL_QUIT;
	SDL_PushEvent(&exit);
}

// here we create the scenes that have been loaded
void SceneManager::createScenes()
{
	// here we just call the onCreate scene for all scenes being stored
	if (!engineScenes.empty())
	{
		for (int i = 0; i < engineScenes.size(); i++) 
		{
			engineScenes[i]->onCreate();
		}
	}

	if (globalScene != NULL)
	{
		globalScene->onCreate();
	}
}

// here we just set the current scene variable
void SceneManager::switchScene(unsigned int ID)
{
	// obviously we check to see the ID points to a valid element in the array
	if (ID < engineScenes.size()) 
	{
		current = ID;
	}
}

// here we just call the update function for all active scenes
void SceneManager::updateScene()
{
	if (globalScene != NULL) 
	{
		globalScene->onUpdate();
	}
	
	if (!engineScenes.empty()) 
	{
		engineScenes[current]->onUpdate();
	}
}