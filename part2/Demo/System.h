
#pragma once

#include "SceneManager.h"
#include "AssetManager.h"
#include "GPU.h"

class OperatingSystem
{
    SceneManager sceneManager;
    AssetManager assetManager;
    Window windowManager;
public:
    OperatingSystem();
    ~OperatingSystem();

    SceneManager* acquireSceneManager();
    AssetManager* acquireAssetManager();
    Window& acquireWindow();

    bool meetsMinimumSpecification();
    bool setupLibraries();

    void releaseLibraries();
    void executeProgram();
};

extern void onApplicationStart(OperatingSystem * os);