
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

#ifndef __LVL__H_
#define __LVL__H_

#include "System.h"
#include "HLGI.h"

// Our main demo level scene class
class Level : public Scene 
{
private:
	// Our local asset manager class
	LocalAssetManager * package;
	// Our deferred render class which implements the technique for us
	DeferredRenderer renderer3D;
	// Our 2D renderer for the HUD
	Renderer2D renderer2D;
	// A window which dimensions are needed for the 3D renderer
	Window * window;
public:
	// Constructor & Deconstructor
	Level(OperatingSystem * os);
	~Level();

	// Handle game and SDL events
	void onGameEvent(SDL_Event& e);
	// Handles when the scene has been created
	void onCreate();
	// Handles when the scene is to be updated
	void onUpdate();
	// Handles when the scene it to be rendered
	void onRender();
private:
	// The randomize lights button
	Button2D switchButton;
	// The terrain for the main scene
	Heightmap terrain;
	// The scenes skybox night sky
	Skybox skybox;
	// The header which is placed at the bottom corner
	Text2D header;
	// The main house model which is drawn in the scene
	Model model;
private:
	// Some private functions to help with the contruction of lights
	glm::vec3 generateRandomColour();
	void generateRandomLights();
};

#endif