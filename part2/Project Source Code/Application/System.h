
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


#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "SceneManager.h"
#include "AssetManager.h"
#include "GPU.h"

// This class represents the system the program runs on
class OperatingSystem
{
private:
	// The scene manager class which will manage multiple application scenes
	SceneManager sceneManager;
	// The asset manager class which will manage multiple assets
	AssetManager assetManager;
	// The window class which will construct a window
	Window windowManager;
	// and a pointer to the GPU so we can grab details about it
	GPU * gpu;
public:
	// Constructor & Deconstructor
	OperatingSystem();
	~OperatingSystem();

	// returns a pointer to the scene manager for the application
	SceneManager * aquireSceneManager();
	// returns a pointer to the asset manager for the application
	AssetManager * aquireAssetManager();
	// returns a pointer to the window for the application
	Window& aquireWindow();
public:
	// returns true if the system meets all requirements
	bool meetsMininumSpecification();
	// returns true if the setup of libraries is successful (SDL/GLEW etc)
	bool setupLibraries();

	// releases the libraries that were previously loaded
	void releaseLibraries();
	// this function starts the program
	void executeProgram();
};

// an external function which the user of the framework applies
extern void onApplicationStart(OperatingSystem * os);

#endif