
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

#include "FirstPersonCamera.h"

// Constructor & De constructor
FirstPersonCamera::FirstPersonCamera()
	: rotation(0.0), pitch(0.0), height(-5.0F), speed(0.3)
{
	// set the initial values for all variables
	viewMatrix = glm::mat4(1.0);
	cameraArea = glm::vec4(-350, -350, 350, 350);
	translate = glm::vec3(0.0, height, 0.0);
	terrainHeight = 0.0f;
	
	// set default key state
	for (int i = 0; i < 4; i++) {
		keys[i] = FALSE;
	}
}

// Alternative copy constructor which copies all data from another camera
FirstPersonCamera::FirstPersonCamera(Camera * camera)
	: rotation(0.0), pitch(0.0), height(-5.0F), speed(0.3)
{
	cameraArea = glm::vec4(-350, -350, 350, 350);
	viewMatrix = camera->getView();
	translate = camera->getPosition();
	height = 0.5f;
	terrainHeight = 0.5f;
	
	// set default key state
	for (int i = 0; i < 4; i++) {
		keys[i] = FALSE;
	}
}

FirstPersonCamera::~FirstPersonCamera()
{
}

// Returns the height of the camera
float FirstPersonCamera::getHeight()
{
	return terrainHeight + height;
}

// returns the view matrix for the camera
glm::mat4& FirstPersonCamera::getView()
{
	return viewMatrix;
}

// handles when the camera is at a point on the terrain
void FirstPersonCamera::handleTerrainHeight(float h)
{
	terrainHeight = height + h;
}

// returns the position of the camera
glm::vec3 FirstPersonCamera::getPosition()
{
	return translate;
}

// The following function handles updating the camera's position based on key pressed
void FirstPersonCamera::updateCameraPosition(SDL_Event& e)
{
	// if we have a keydown event
	if (e.type == SDL_KEYDOWN) 
	{
		// change the key state variable accordingly
		switch (e.key.keysym.sym) {
			case SDLK_w: keys[0] = TRUE;  break;
			case SDLK_s: keys[1] = TRUE;  break;
			case SDLK_a: keys[2] = TRUE;  break;
			case SDLK_d: keys[3] = TRUE;  break;
				default:
					break;
		}
	}

	// if we have a key up event
	if (e.type == SDL_KEYUP) 
	{
		/ change the key state variable accordingly
		switch (e.key.keysym.sym) {
			case SDLK_w: keys[0] = FALSE;  break;
			case SDLK_s: keys[1] = FALSE;  break;
			case SDLK_a: keys[2] = FALSE;  break;
			case SDLK_d: keys[3] = FALSE;  break;
		default:
			break;
		}
	}

	// if we have a mouse motion event we rotate the camera and calculate the pitch of the camera as well
	if (e.type == SDL_MOUSEMOTION && e.button.button == SDL_BUTTON_LEFT) 
	{
		// x magnitude = rotation
		rotation += e.motion.xrel;
		// y magnitude = rotation
		pitch += e.motion.yrel;
		
		// make sure to keep the degrees in readable form
		if (rotation < 0) {
			rotation = 360;
		}

		if (rotation > 360) {
			rotation = 0;
		}
	}
}

// the following sets the new position of the camera
void FirstPersonCamera::setPosition(glm::vec3 position)
{
	// calculate where to translate the camera to
	translate = -position;
	translate.z = position.z;
	terrainHeight = -position.y;
	// calculate the height of the camera
	height = -position.y;
}

// this function applies the new position to the view matrix
void FirstPersonCamera::repositionCamera()
{
	// reset the view matrix
	viewMatrix = glm::mat4(1.0);
	viewMatrix = glm::rotate(viewMatrix, pitch, glm::vec3(1.0, 0.0, 0.0));
	viewMatrix = glm::rotate(viewMatrix, rotation, glm::vec3(0.0, 1.0, 0.0));

	// then calculate the temporary position
	glm::vec3 temp = translate;

	temp.y += ((terrainHeight)-translate.y) / 5.0;

	// calculate the direction of travel
	if (keys[0]) {
		temp += glm::vec3(sin(glm::radians(-rotation)), 0.0, cos(glm::radians(-rotation))) * speed;
	} if (keys[1]) {
		temp += glm::vec3(-sin(glm::radians(-rotation)), 0.0, -cos(glm::radians(-rotation)))  * speed;
	} if (keys[2]) {
		temp += glm::vec3(cos(glm::radians(-rotation)), 0.0, -sin(glm::radians(-rotation)))  * speed;
	} if (keys[3]) {
		temp += glm::vec3(-cos(glm::radians(-rotation)), 0.0, sin(glm::radians(-rotation)))  * speed;
	}

	// and only apply the new position if within a given area
	if (temp.x >= cameraArea.x && temp.x <= cameraArea.w && temp.z >= cameraArea.y && temp.z <= cameraArea.w)
	{
		translate = temp;
	}

	// apply the transformation
	viewMatrix = glm::translate(viewMatrix, translate);
}