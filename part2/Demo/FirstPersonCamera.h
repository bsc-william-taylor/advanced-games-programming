
#pragma once

#include "Framework.h"
#include "Camera.h"

class FirstPersonCamera : public Camera
{
    glm::mat4 viewMatrix;
    glm::vec4 cameraArea;
    glm::vec3 translate;

    GLfloat terrainHeight;
    GLfloat rotation;
    GLfloat pitch;
    GLfloat speed;
    GLfloat height;
    GLint keys[4];
public:
    FirstPersonCamera(Camera*);
    FirstPersonCamera();
    ~FirstPersonCamera();

    glm::vec3 getPosition();
    glm::mat4& getView();

    void updateCameraPosition(SDL_Event&);
    void handleTerrainHeight(float);
    void setPosition(glm::vec3 p);
    void repositionCamera();

    GLfloat getHeight();
};