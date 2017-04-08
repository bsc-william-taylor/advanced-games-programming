
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

#include "main.h"

// this main function is supplied by the 3D framework
void onApplicationStart(OperatingSystem * operatingSystem) {

	// first we acquire the window object
	Window * window = &operatingSystem->aquireWindow();

	// set the properties and create it
	window->setPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	window->setTitle("AGP Part 2 - B00235610 - 49 Dynamic Point Lights 100+ FPS");
	window->setSize(1050, 650);
	window->create();

	// then acquire the scene manager 
	SceneManager * scenes = operatingSystem->aquireSceneManager();

	// push back the 2 main scenes in the application
	scenes->packSceneList({ 
		new Menu(operatingSystem),
		new Level(operatingSystem)
	});

	// and start the application
	operatingSystem->executeProgram();
}