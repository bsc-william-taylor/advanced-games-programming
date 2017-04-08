
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

#include "level.h"
#include "main.h"

// Constructor & Deconstructor
Level::Level(OperatingSystem * engine) 
{
	// Acquire a pointer to the os's window
	window = &engine->aquireWindow();

	// Acquire a new local asset manager
	package = engine->aquireAssetManager()->grabLocalManager();

	// and load the following assets
	package->grab({ "data/grass.png",
		"data/heightmap.png",
		"data/Aller_Rg.ttf",
		"data/scheune.3DS",
		"data/front.png",
		"data/right.png",
		"data/back.png",
		"data/left.png",
		"data/top.png"
	});
}

Level::~Level() 
{
	// Package needs to be deleted by the scene itself
	SAFE_RELEASE(package);
}

// Handles when the scene is created
void Level::onCreate() 
{
	// load the terrain from the height map texture then set its X and Y scales
	terrain.create(package->getT("data/grass"), "data/heightmap.png", 1.0, 12.5);
	// load the main house model as well
	model.setModel(package->getM("data/scheune"));

	// set the distance of the skybox from the camera
	skybox.setDistance(500.0);
	// Pass through each skybox texture to the class for rendering
	skybox.createSkybox({ 
		package->getT("data/front"),
		package->getT("data/right"),
		package->getT("data/back"),
		package->getT("data/left"),
		package->getT("data/top"),
		package->getT("data/top")
	});

	// then create our 2D renderer
	renderer2D.createRenderer();

	// then create out 3D deferred renderer which requires the dimensions of the window
	renderer3D.createRenderer(window->getWidth(), window->getHeight());
	// then set the initial camera for the scene and its position & the direction light
	renderer3D.changeCamera(FIRST_PERSON);
	renderer3D.setCameraPosition(glm::vec3(0.0, 2.0, -35.0));
	renderer3D.getLightPosition() = glm::vec3(0.0, -0.5, 1.0);

	// create our really long string which list the features in the demo
	std::string labelText = "Features : Deferred rendering, multiple light types, heightmap generation, ";
	labelText += "light volumes and cubemaps";

	// load our header text
	header.setFont(package->getL("data/Aller_Rg", 30, { 255, 255, 255 }), labelText.c_str());
	header.setArea(glm::vec2(1900, 30), ALIGNMENT::LEFT);
	
	// and load the button as well
	switchButton.setButtonText(package->getL("data/Aller_Rg", 40, { 255, 255, 255 }), "Randomize Lights");
	switchButton.setArea(glm::vec4(10, 1030, 500, 200), ALIGNMENT::RIGHT);

	// then generate some random lights for the scene
	generateRandomLights();
}

// handle SDL events
void Level::onGameEvent(SDL_Event& e) 
{
	// pass each SDL event to the renderer which will update the camera
	renderer3D.updateCamera(e);

	// if the switch lights button has been pressed
	if (switchButton.isPressed(e))
	{
		generateRandomLights();
	}
}

// Handle os updates
void Level::onUpdate() 
{
	// Handle the cameras height which should be based on the terrains height
	renderer3D.handleTerrainHeight(&terrain);
	// then re position the camera
	renderer3D.repositionCamera();
}

// Render the scene for the user
void Level::onRender() 
{
	// Create our matrices
	glm::mat4 projectionMatrix = glm::mat4();
	glm::mat4 modelMatrix = glm::mat4();

	// then set the projection matrix
	projectionMatrix = glm::perspective(75.0f, 1920.0f / 1080.0f, 0.1f, 1000.0f);

	// then set the initial model matrix
	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0, -2.05, 0.0));
	modelMatrix = glm::rotate(modelMatrix, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.005, 0.005, 0.005));

	// prepare the renderer for rendering
	renderer3D.prepare();
	// send the matrices to the shader
	renderer3D.setMatrixForObject("projection", projectionMatrix);
	renderer3D.setMatrixForObject("model", modelMatrix);
	// then render our house model
	renderer3D.renderModel(&model);

	// render the skybox and the terrain which are both centered
	renderer3D.renderSkybox(&skybox);
	renderer3D.renderMap(&terrain);
	
	// then present the final image
	renderer3D.present();

	// then switch to a 2D projection 
	projectionMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::ortho(0.0, 1920.0, 0.0, 1080.0, -1.0, 1.0);

	// prepare the renderer
	renderer2D.prepare();
	// send the matrices to the shader
	renderer2D.setMatrixForObject("projection", projectionMatrix);
	renderer2D.setMatrixForObject("model", glm::mat4());

	// then render the label and the buttons then present the final image
	renderer2D.renderButton(&switchButton);
	renderer2D.renderLabel(&header);
	renderer2D.present();
}

// generates 49 random lights for us
void Level::generateRandomLights()
{
	// here we create a vector of lights to pass to the renderer
	std::vector<PointLight> pointLights;
	// pre allocate some memory for the point lights
	pointLights.reserve(49);

	// iterate through each spot we want to place a light
	for (int i = -24; i < 32; i += 8)
	{
		for (int b = -24; b < 32; b += 8)
		{
			// push a new light into the vector (using std::initializer_list())
			pointLights.push_back({
				8.0, glm::vec3(i, 0.0, b),
				generateRandomColour(),
				0.1f, 0.0f,	0.0f, 0.3f
			});
		}
	}	

	// then hand the vector to the renderer
	renderer3D.pushLights(pointLights);
	// construct the global UBO for all the lights
	renderer3D.constructUBO();
}

// Generates a random colour vector in GL format -> RGB (0 - 1, 0 - 1, 0 - 1)
glm::vec3 Level::generateRandomColour()
{
	// create the colour vector
	glm::vec3 colour = glm::vec3(0, 0, 0);
	
	// generate random colour values
	colour.r = ((rand() % 101) / 100.0f);
	colour.g = ((rand() % 101) / 100.0f);
	colour.b = ((rand() % 101) / 100.0f);

	// return it to the user (here i double the colour intensity)
	return colour * glm::vec3(2.25, 2.25, 2.25);
}