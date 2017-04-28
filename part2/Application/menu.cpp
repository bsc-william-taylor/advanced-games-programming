
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

// Constructor & Deconstructor
Menu::Menu(OperatingSystem * system)
{
	// acquire the scene manager
	scenes = system->aquireSceneManager();
	// acquire a local asset manager for the scene
	package = system->aquireAssetManager()->grabLocalManager();
	// and grab these assets from disk
	package->grab({ "data/background.png",
		"data/Aller_Rg.ttf",
	});
}

Menu::~Menu() 
{
	// Packages need to be manually deleted
	SAFE_RELEASE(package);
}

// Handles when the scene is created
void Menu::onCreate()
{
	// Load all assets starting with the header
	header.setFont(package->getL("data/Aller_Rg", 150, { 255, 255, 255 }), "AGP Part 2 - B00235610");
	header.setArea(glm::vec2(1920/2, 900), ALIGNMENT::CENTER);

	// Load the play button set the font, text and location
	playDemoButton.setButtonText(package->getL("data/Aller_Rg", 100, {255, 255, 255}), "Start tech demo");
	playDemoButton.setArea(glm::vec4(1920 / 2 - 250, 300, 500, 100), ALIGNMENT::CENTER);

	// Load the background texture and make it fullscreen
	background.setTexture(package->getT("data/background"));
	background.setArea(glm::vec4(0.0, 0.0, 1920, 1080));
	
	// finally create the 2D renderer
	renderer2D.createRenderer();
}

// Handle SDL / Game events
void Menu::onGameEvent(SDL_Event& e) 
{
	// if the play button has been pressed
	if (playDemoButton.isPressed(e))
	{
		// go to the lvl scene
		scenes->switchScene((unsigned)SceneID::LVL);
	}
}

// nothing needs updating so this can be empty
void Menu::onUpdate() 
{
}

// Handles when the scene is rendered
void Menu::onRender()  
{
	// create our matrices
	glm::mat4 projectionMatrix = glm::mat4();
	glm::mat4 modelMatrix = glm::mat4();

	// set the projection matrix
	projectionMatrix = glm::ortho(0.0, 1920.0, 0.0, 1080.0, -1.0, 1.0);

	// then prepare our 2d render send out matrices over
	renderer2D.prepare();
	renderer2D.setMatrixForObject("projection", projectionMatrix);
	renderer2D.setMatrixForObject("model", modelMatrix);

	// then render each object in order
	renderer2D.renderTexture(&background);
	renderer2D.renderButton(&playDemoButton);
	renderer2D.renderLabel(&header);

	// then present the final image
	renderer2D.present();
}