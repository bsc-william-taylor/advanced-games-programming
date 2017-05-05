
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

    SceneManager * acquireSceneManager();
    AssetManager * acquireAssetManager();
    Window& aquireWindow();

    bool meetsMininumSpecification();
    bool setupLibraries();

    void releaseLibraries();
    void executeProgram();
};

extern void onApplicationStart(OperatingSystem * os);