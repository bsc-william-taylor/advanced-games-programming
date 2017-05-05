
#include "FirstPersonCamera.h"

FirstPersonCamera::FirstPersonCamera()
    : rotation(0.0), pitch(0.0), height(-5.0F), speed(0.3)
{
    viewMatrix = glm::mat4(1.0);
    cameraArea = glm::vec4(-350, -350, 350, 350);
    translate = glm::vec3(0.0, height, 0.0);
    terrainHeight = 0.0f;

    for (int i = 0; i < 4; i++)
    {
        keys[i] = FALSE;
    }
}

FirstPersonCamera::FirstPersonCamera(Camera * camera)
    : rotation(0.0), pitch(0.0), height(-5.0F), speed(0.3)
{
    cameraArea = glm::vec4(-350, -350, 350, 350);
    viewMatrix = camera->getView();
    translate = camera->getPosition();
    height = 0.5f;
    terrainHeight = 0.5f;

    for (int i = 0; i < 4; i++)
    {
        keys[i] = FALSE;
    }
}

FirstPersonCamera::~FirstPersonCamera()
{
}

float FirstPersonCamera::getHeight()
{
    return terrainHeight + height;
}

glm::mat4& FirstPersonCamera::getView()
{
    return viewMatrix;
}

void FirstPersonCamera::handleTerrainHeight(float h)
{
    terrainHeight = height + h;
}

glm::vec3 FirstPersonCamera::getPosition()
{
    return translate;
}

void FirstPersonCamera::updateCameraPosition(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym) {
        case SDLK_w: keys[0] = TRUE;  break;
        case SDLK_s: keys[1] = TRUE;  break;
        case SDLK_a: keys[2] = TRUE;  break;
        case SDLK_d: keys[3] = TRUE;  break;
        default:
            break;
        }
    }
    if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym) {
        case SDLK_w: keys[0] = FALSE;  break;
        case SDLK_s: keys[1] = FALSE;  break;
        case SDLK_a: keys[2] = FALSE;  break;
        case SDLK_d: keys[3] = FALSE;  break;
        default:
            break;
        }
    }

    if (e.type == SDL_MOUSEMOTION && e.button.button == SDL_BUTTON_LEFT)
    {
        rotation += e.motion.xrel;
        pitch += e.motion.yrel;

        if (rotation < 0) {
            rotation = 360;
        }

        if (rotation > 360) {
            rotation = 0;
        }
    }
}

void FirstPersonCamera::setPosition(glm::vec3 position)
{
    translate = -position;
    translate.z = position.z;
    terrainHeight = -position.y;
    height = -position.y;
}

void FirstPersonCamera::repositionCamera()
{
    viewMatrix = glm::mat4(1.0);
    viewMatrix = glm::rotate(viewMatrix, pitch, glm::vec3(1.0, 0.0, 0.0));
    viewMatrix = glm::rotate(viewMatrix, rotation, glm::vec3(0.0, 1.0, 0.0));

    glm::vec3 temp = translate;

    temp.y += ((terrainHeight)-translate.y) / 5.0;

    if (keys[0]) {
        temp += glm::vec3(sin(glm::radians(-rotation)), 0.0, cos(glm::radians(-rotation))) * speed;
    } if (keys[1]) {
        temp += glm::vec3(-sin(glm::radians(-rotation)), 0.0, -cos(glm::radians(-rotation)))  * speed;
    } if (keys[2]) {
        temp += glm::vec3(cos(glm::radians(-rotation)), 0.0, -sin(glm::radians(-rotation)))  * speed;
    } if (keys[3]) {
        temp += glm::vec3(-cos(glm::radians(-rotation)), 0.0, sin(glm::radians(-rotation)))  * speed;
    }

    if (temp.x >= cameraArea.x && temp.x <= cameraArea.w && temp.z >= cameraArea.y && temp.z <= cameraArea.w)
    {
        translate = temp;
    }

    viewMatrix = glm::translate(viewMatrix, translate);
}