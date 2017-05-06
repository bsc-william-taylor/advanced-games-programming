
#pragma once

#include "Renderer.h"

class SceneManager;

class Scene
{
public:
    virtual void onUpdate(SceneManager&, Renderer&) = 0;
    virtual void onEvent(SceneManager&, SDL_Event *) = 0;
    virtual void onLoad(SceneManager&, Renderer&) = 0;
    virtual void onRender(Renderer&) = 0;
    virtual void onEnter() {}
    virtual void onExit() {}
    virtual ~Scene() {}
};

class SceneManager
{
    std::vector<Scene *> scenes;
    unsigned int index;
public:
    SceneManager();
    ~SceneManager();

    void prepareScenes(Renderer& renderer);
    void putScenes(std::initializer_list<Scene *> scenes);
    void setScene(unsigned ID);

    Scene * getScene(unsigned int ID);
    Scene * getCurrent();
};
