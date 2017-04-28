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

#include "ExternalLibraries.h"
#include "CommonHeader.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "Bank.h"
#include "Window.h"

// The type of mode you want the game to be played in
enum DeployType {
	RELEASE_DEPLOY,
	DEBUG_DEPLOY
};

// The main game class
class Game
{
private:
	// a class that manages all external libraries
	ExternalLibraries gameLibrarys;
	// our scene manager which controls game scenes
	SceneManager * gameScenes;
	// our game renderer which will render game objects
	Renderer * renderer;
	// the window which our game will be rendererd in
	Window * window;
	// the asset bank which allows assets to be shared accross multiple devices
	Bank * bank;
public:
	// Constructor & Deconstructor
	Game();
	~Game();
public:
	// Creates the window at the select position
	void createWindow(int x, int y, int w, int h);
	// deploys the application and also calls the function you specifiy so the user can delete bank objects
	void begin(DeployType option, std::function<void(Bank*bank)> cleanupFunc = [](Bank*){});
	// returns the scene manager as a pointer
	SceneManager * getSceneManager();
	// returns the bank as a pointer
	Bank * getGameBank();
};
