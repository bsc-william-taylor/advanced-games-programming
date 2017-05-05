
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
    // the current scene ID
    unsigned int current;
    // a pointer to the window
    Window * window;
    // a pointer to a global which is always updated
    Scene * globalScene;
public:
    // Constructor & Deconstructor
    SceneManager(Window * w);
    ~SceneManager();

    // packs a list of scenes into the vector
    void packSceneList(std::initializer_list<Scene*> list);
    // set the global scene that will always be updated
    void setGlobalScene(Scene*);
    // notify's the active scenes about the SDL_Event
    void handeEventScene(SDL_Event& e);
    // creates and inits the scenes
    void createScenes();
    // calls the render function of the scenes
    void renderScene();
    // calls the update function of the scenes
    void updateScene();
    // switches the current active scene
    void switchScene(unsigned int ID);
    // closes the scene manager and quits the application 
    void exit();
};