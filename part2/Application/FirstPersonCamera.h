
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

#include "Framework.h"
#include "Camera.h"

class FirstPersonCamera : public Camera 
{
private:
	// The view matrix for the camera
	glm::mat4 viewMatrix;
	// The area the camera can walk around in
	glm::vec4 cameraArea;
	// The current movement value
	glm::vec3 translate;

	// the terrain height at the cameras point
	GLfloat terrainHeight;
	// the rotation of the camera
	GLfloat rotation;
	// the pitch of the camera
	GLfloat pitch;
	// the camera speed of movement
	GLfloat speed;
	// the height of the camera
	GLfloat height;
	// key state variables
	GLint keys[4];
public:
	// Constructors and Deconstructor
	FirstPersonCamera(Camera *);
	FirstPersonCamera();
	~FirstPersonCamera();

	// returns a copy of the current position
	glm::vec3 getPosition();
	// returns the view matrix as a reference
	glm::mat4& getView();

	// this function will updates the camera based on the key being pressed
	void updateCameraPosition(SDL_Event&);
	// this function will reposition the camera to a certain height
	void handleTerrainHeight(float);
	// this function will set the position of the camera
	void setPosition(glm::vec3 p);
	// this function will reposition the camera by updating the view matrix
	void repositionCamera();

	// finally this function returns the height of the camera in 3D space
	GLfloat getHeight();
};