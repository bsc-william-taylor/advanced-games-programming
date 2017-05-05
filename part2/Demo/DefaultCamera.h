
#pragma once

#include "Camera.h"

class DefaultCamera : public Camera
{
    glm::mat4 viewMatrix;
public:
    DefaultCamera();
    ~DefaultCamera();

    glm::vec3 getPosition();
    glm::mat4& getView();

    void updateCameraPosition(SDL_Event&);
    void handleTerrainHeight(float f);
    void setPosition(glm::vec3);
    void repositionCamera();

    GLfloat getHeight();
};