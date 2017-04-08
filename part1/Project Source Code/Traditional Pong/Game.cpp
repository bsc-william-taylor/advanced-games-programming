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

#include "highPrecisionTimer.h"
#include "Texture.h"
#include "Game.h"

// Constructor & Deconstructor
Game::Game()
	: window(NULL)
{
	// setup each game object/component
	gameScenes = new SceneManager();
	renderer = new Renderer();
	bank = new Bank();

	// then import the libraries needed
	gameLibrarys.importLibraries();
}

Game::~Game()
{
	// release all objects
	SAFE_RELEASE(gameScenes);
	SAFE_RELEASE(renderer);
	SAFE_RELEASE(window);
	SAFE_RELEASE(bank);

	// and export libraries
	gameLibrarys.exportLibraries();
	delete EventManager::get();
}

// starts / begins the application
void Game::begin(DeployType type, std::function<void(Bank*)> cleanupFunc)
{
	// providing we have setup a window
	if(window != NULL)
	{
		// determine the deploy type
		type == RELEASE_DEPLOY ?
			window->makeFullscreenWindow() :	// if in release mode launch a fullscreen window
			window->makeSimpleWindow();			// else launch a simple window

		// make a simple renderer for the window
		renderer->makeSimpleRenderer(window);
		// prepare all scenes for application start
		gameScenes->prepareScenes(*renderer);

		// set rand to be truly random
		srand((unsigned)time(NULL));
		// and create a high precision timer for frame limiting
		HighPrecisionTimer timer;

		// while the window is open
		while(window->isOpen())
		{
			// get the current game scene
			Scene * current = gameScenes->getCurrent();
			// start the frame timer
			timer.start();

			// Loop through all OS events
			SDL_Event e;
			while(SDL_PollEvent(&e) != NULL)
			{
				// if we have a quit event
				if(e.type == SDL_QUIT)
				{
					// close the window and break
					window->close();
					break;
				}

				// is we have a mouse input event
				if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
				{
					// scale it position for the applications window
					int w = 0;
					int h = 0;

					SDL_GetWindowSize(window->getWindow(), &w, &h);

					e.motion.x *= ((float)1920/w);
					e.motion.y *= ((float)1080/h);
				}
	
				// then provide any and all events to the game scenes
				current->onEvent((*gameScenes), &e);
			}

			// after all events have been processes clear the window
			renderer->clear(window);

			// then tell all events to perform activation checks
			EventManager::get()->PerformChecks();
			// then update all objects
			current->onUpdate(*gameScenes, *renderer);
			// then render the scene
			current->onRender(*renderer);
			// swap the windows buffer to show rendered screen
			renderer->swap();

			// stop the frame timer
			timer.stop();

			// then wait till 16ms has passed
			while (timer.elapsed(NS) < (float)(1.0e9 / window->getRefreshRate()));
		}
	}
	
	// call the users cleanup function when the game has closed
	cleanupFunc(bank);
}

// creates a window for the user
void Game::createWindow(int x, int y, int w, int h)
{
	// we only allow this function to be called once
	if (window == NULL)
	{
		// create the window and set its position
		window = new Window();
		window->setPosition(x, y);
		window->setSize(w, h);
	}
	else
	{
		// if called for a second time throw an exception
		throw Error(WINDOW, "Error multiple windows are not supported", WILLIAM);
	}
}

// returns a pointer to the scene manager
SceneManager * Game::getSceneManager()
{
	return gameScenes;
}

// returns a pointer to the games bank
Bank * Game::getGameBank()
{
	return bank;
}