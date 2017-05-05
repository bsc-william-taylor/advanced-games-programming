
#pragma once

#include "System.h"
#include "DeferredRenderer.h"
#include "Heightmap.h"
#include "Button2D.h"
#include "Renderer2D.h"
#include "Model.h"

class Level : public Scene
{
private:
    LocalAssetManager* package;
    DeferredRenderer renderer3D;
    Renderer2D renderer2D;
    Button2D switchButton;
    Heightmap terrain;
    Window* window;
    Skybox skybox;
    Text2D header;
    Model model;
public:
    Level(OperatingSystem* os);
    ~Level();

    void generateRandomLights();
    void onGameEvent(SDL_Event& e);
    void onCreate();
    void onUpdate();
    void onRender();

    glm::vec3 generateRandomColour();
};

