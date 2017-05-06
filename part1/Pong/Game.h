
#pragma once

#include "ExternalLibraries.h"
#include "MajorInclude.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "Bank.h"
#include "Window.h"

enum DeployType 
{
    RELEASE_DEPLOY,
    DEBUG_DEPLOY
};

class Game
{
    ExternalLibraries gameLibrarys;
    SceneManager * gameScenes;
    Renderer * renderer;
    Window * window;
    Bank * bank;
public:
    Game();
    ~Game();

    void createWindow(int x, int y, int w, int h);
    void begin(DeployType option, std::function<void(Bank*bank)> cleanupFunc = [](Bank*) {});

    SceneManager * getSceneManager();
    Bank * getGameBank();
};
