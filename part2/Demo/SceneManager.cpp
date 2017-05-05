
#include "SceneManager.h"

SceneManager::SceneManager(Window * w)
{
    engineScenes.reserve(10);
    globalScene = NULL;
    current = NULL;
    window = w;
}

SceneManager::~SceneManager()
{
}

void SceneManager::setGlobalScene(Scene * scene)
{
    globalScene = scene;
}

void SceneManager::packSceneList(std::initializer_list<Scene *> scenes)
{
    for (auto& scene : scenes)
    {
        engineScenes.push_back(scene);
    }
}

void SceneManager::renderScene()
{
    if (!engineScenes.empty())
    {
        engineScenes[current]->onRender();
    }

    if (globalScene != NULL)
    {
        globalScene->onRender();
    }
}

void SceneManager::handeEventScene(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) 
    {
        SDL_Event exit;
        exit.type = SDL_QUIT;
        SDL_PushEvent(&exit);
    }

    if (e.type == SDL_MOUSEMOTION || e.button.button == SDL_BUTTON_LEFT)
    {
        int w = 0;
        int h = 0;

        SDL_GetWindowSize(window->getWindow(), &w, &h);

        e.motion.x *= ((float)1920 / w);
        e.motion.y *= ((float)1080 / h);
        e.motion.y = 1080 - e.motion.y;
    }

    if (!engineScenes.empty())
    {
        engineScenes[current]->onGameEvent(e);
    }

    if (globalScene != NULL)
    {
        globalScene->onGameEvent(e);
    }
}

void SceneManager::exit()
{
    SDL_Event exit;
    exit.type = SDL_QUIT;
    SDL_PushEvent(&exit);
}

void SceneManager::createScenes()
{
    if (!engineScenes.empty())
    {
        for (int i = 0; i < engineScenes.size(); i++)
        {
            engineScenes[i]->onCreate();
        }
    }

    if (globalScene != NULL)
    {
        globalScene->onCreate();
    }
}

void SceneManager::switchScene(unsigned int ID)
{
    if (ID < engineScenes.size())
    {
        current = ID;
    }
}

void SceneManager::updateScene()
{
    if (globalScene != NULL)
    {
        globalScene->onUpdate();
    }

    if (!engineScenes.empty())
    {
        engineScenes[current]->onUpdate();
    }
}