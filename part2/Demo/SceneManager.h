
#pragma once

#include "Framework.h"
#include "Process.h"
#include "Window.h"

class Scene
{
public:
    virtual void onGameEvent(SDL_Event& e) {}
    virtual void onRender() {}
    virtual void onCreate() {}
    virtual void onUpdate() {}
    virtual ~Scene() {}
};

class SceneManager
{
    std::vector<Scene*> engineScenes;
    unsigned int current;
    Window* window;
    Scene* globalScene;
public:
    SceneManager(Window * w);
    ~SceneManager();

    void packSceneList(std::initializer_list<Scene*> list);
    void setGlobalScene(Scene*);
    void handeEventScene(SDL_Event& e);
    void createScenes();
    void renderScene();
    void updateScene();
    void switchScene(unsigned int ID);
    void exit();
};