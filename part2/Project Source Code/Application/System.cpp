
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


#include "HighPrecisionTimer.h"
#include "System.h"

// Constructor & Deconstructor
OperatingSystem::OperatingSystem()
	: sceneManager(&windowManager)
{
}

OperatingSystem::~OperatingSystem()
{
}

// Setup the libraries for the application
bool OperatingSystem::setupLibraries()
{
	bool setupSuccess = true;

	// if SDL fails to initialize
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		// set the return type to false
		setupSuccess = false;
	}

	int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
	// if IMG fails to initialize
	if (IMG_Init(flags) != flags)
	{
		// set the return type to false
		setupSuccess = false;
	}

	// if TTF fails to initialize
	if (TTF_Init() == -1)
	{
		// set the return type to false
		setupSuccess = false;
	}

	// then setup srand for random number generation & freeimage which never fails to setup
	srand((unsigned)time(NULL));
	FreeImage_Initialise();

	// return the success message
	return setupSuccess;
}

// returns true if the system has the hardware && software to support the framework && application
bool OperatingSystem::meetsMininumSpecification()
{
	// for now all we check for is OPENGL 3.3+
	return (gpu->has(OPENGL, 3.3));
}

// Here we just release all libraries loaded if they were loaded successfult=ly
void OperatingSystem::releaseLibraries()
{
	// release freeimage first
	FreeImage_DeInitialise();

	// Then all SDL_Ext libraries and SDL itself 
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

// The following functino executes the program
void OperatingSystem::executeProgram()
{
	// Create a frametime to lock the framerate
	HighPrecisionTimer frameTimer;

	// Create a variable to store system events
	SDL_Event operatingSystemEvents;
	// and a variable to tell when the application should end
	SDL_bool run = SDL_TRUE;

	// initialise the GPU
	gpu = new GPU(true);

	// check for minimum specification
	if (meetsMininumSpecification())
	{
		// then create all application scenes
		sceneManager.createScenes();

		// while we should run at the application
		while (run)
		{
			// start the frame timer
			frameTimer.start();

			// then poll all system events
			while (SDL_PollEvent(&operatingSystemEvents))
			{
				// if the message is quit just quit the application
				if (operatingSystemEvents.type == SDL_QUIT)
				{
					run = SDL_FALSE;
					break;
				}
				else
				{
					// else send each one, one by one to the active scene
					sceneManager.handeEventScene(operatingSystemEvents);
				}
			}
			
			// then call both the scenes render and update methods
			sceneManager.updateScene();
			sceneManager.renderScene();

			// then swap the windows buffer to reveal the final image
			windowManager.swapBuffers();

			// and wait till 16.6666 MS have passed to ensure the game renders at 60.0 frames per second
			while (frameTimer.elapsed(NS) <= (float)(1.0e9 / 60.00F));
		}
	}

	// on exit release the GPU object
	SAFE_RELEASE(gpu);
}

// return a pointer to the window 
Window& OperatingSystem::aquireWindow()
{
	return windowManager;
}

// return a pointer to the asset manager
AssetManager * OperatingSystem::aquireAssetManager()
{
	return &assetManager;
}

// returns a pointer to the scene manager
SceneManager * OperatingSystem::aquireSceneManager()
{
	return &sceneManager;
}

// This is the main function which is controlled by the framework, the user must implement onApplicationStart instead
int main(int argc, char ** argv) 
{
	// set the message to be returned upon successful execution of the program
	int message = EXIT_SUCCESS;

	// handle all exceptions thrown
	try 
	{
		// Create the system the application will run on
		OperatingSystem system;
	
		// if all libraries are setup properly
		if (system.setupLibraries())
		{
			// call the users main method and provide the system we created
			onApplicationStart(&system);
			// then release all libraries after the application has finished
			system.releaseLibraries();
		}
		else
		{
			// if libraries cant be setup then set the message to a fail message and never start the program
			message = EXIT_FAILURE;
		}
	}
	catch (Error e) 
	{
		// when an exception is throw set the ending message to a fail message
		message = EXIT_FAILURE;
		// and show a message box giving details on the problem encountered
		SDL_ShowSimpleMessageBox(NULL,
			e.title(),
			e.what(),
			NULL
		);
	}

	// return the message back to the system
	return message;
}