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

#include "Renderer.h"

class SceneManager;

// the interface for all game scenes
class Scene
{
public:
	// all scenes should implement these functions
	virtual void onUpdate(SceneManager&, Renderer&) = 0;
	virtual void onEvent(SceneManager&, SDL_Event *) = 0;
	virtual void onLoad(SceneManager&, Renderer&) = 0;
	virtual void onRender(Renderer&) = 0;
	virtual void onEnter() {}
	virtual void onExit() {}
	virtual ~Scene() {}
};

// A manager for all game scenes
class SceneManager
{
private:
	// a list of all game scenes
	std::vector<Scene *> scenes;
	// a index variable to the current scene
	unsigned int index;
public:
	// Constructor & Deconstructor
	SceneManager();
	~SceneManager();

	// inits all scenes
	void prepareScenes(Renderer& renderer);
	// puts a list of scenes into the vector
	void putScenes(std::initializer_list<Scene *> scenes);
	// sets the current scene
	void setScene(unsigned ID);
	// returns a pointer to a specific scene
	Scene * getScene(unsigned int ID);
	// returns the current scene
	Scene * getCurrent();
};
