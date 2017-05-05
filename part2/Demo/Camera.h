
#pragma once

#include "Framework.h"
#include "math.h"

enum class CameraType
{
    FirstPerson,
    DefaultCamera
};

class Camera
{
public:
    virtual void updateCameraPosition(SDL_Event& w) = 0;
    virtual void handleTerrainHeight(GLfloat h) = 0;
    virtual void setPosition(glm::vec3 p) = 0;
    virtual glm::vec3 getPosition() = 0;
    virtual void repositionCamera() = 0;
    virtual glm::mat4& getView() = 0;
    virtual float getHeight() = 0;
    virtual ~Camera() {}
};