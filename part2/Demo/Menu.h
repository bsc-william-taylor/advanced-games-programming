
#pragma once

#include "System.h"
#include "DeferredRenderer.h"
#include "Heightmap.h"
#include "Button2D.h"
#include "Renderer2D.h"
#include "Model.h"

class Menu : public Scene
{
    LocalAssetManager* package;
    SceneManager* scenes;

    Renderer2D renderer2D;
    Texture2D background;
    Button2D playDemoButton;
    Text2D header;
public:
    Menu(OperatingSystem* os);
    ~Menu();

    void onGameEvent(SDL_Event& e);
    void onCreate();
    void onUpdate();
    void onRender();
};