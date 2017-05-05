
#pragma once

#include "System.h"
#include "HLGI.h"

class Menu : public Scene
{
    LocalAssetManager* package;
    SceneManager* scenes;

    Renderer2D renderer2D;
    Texture2D background;
    Button2D playDemoButton;
    Text2D header;
public:
    Menu(OperatingSystem * os);
    ~Menu();

    void onGameEvent(SDL_Event& e);
    void onCreate();
    void onUpdate();
    void onRender();
};