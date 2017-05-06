
#include "SceneManager.h"

SceneManager::SceneManager()
    : index(NULL)
{
}

SceneManager::~SceneManager()
{
    for (auto&& scene : scenes)
    {
        delete scene;
    }
}

Scene * SceneManager::getScene(unsigned int ID)
{
    return scenes[ID];
}

void SceneManager::prepareScenes(Renderer& renderer)
{
    for (auto&& scene : scenes)
    {
        scene->onLoad(*this, renderer);
    }
}

void SceneManager::putScenes(std::initializer_list<Scene *> gameScenes)
{
    for (auto&& s : gameScenes)
    {
        if (s != NULL)
        {
            scenes.push_back(s);
        }
    }
}

void SceneManager::setScene(unsigned ID)
{
    if (scenes.empty())
    {
        index = ID;
    }
    else
    {
        if (ID < scenes.size())
        {
            scenes[index]->onExit();
            scenes[ID]->onEnter();
            index = ID;
        }
        else
        {
            throw Error(GAME, "Invalid scene ID");
        }
    }
}

Scene * SceneManager::getCurrent()
{
    return scenes[index];
}
