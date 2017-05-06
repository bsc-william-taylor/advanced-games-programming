
#include "highPrecisionTimer.h"
#include "Texture.h"
#include "Game.h"

Game::Game()
    : window(NULL)
{
    gameScenes = new SceneManager();
    renderer = new Renderer();
    bank = new Bank();

    gameLibrarys.importLibraries();
}

Game::~Game()
{
    SAFE_RELEASE(gameScenes);
    SAFE_RELEASE(renderer);
    SAFE_RELEASE(window);
    SAFE_RELEASE(bank);

    gameLibrarys.freeLibraries();
    delete EventManager::get();
}

void Game::begin(DeployType type, std::function<void(Bank*)> cleanupFunc)
{
    if (window != NULL)
    {
        type == RELEASE_DEPLOY ? window->makeFullscreenWindow() : window->makeSimpleWindow();
        renderer->makeSimpleRenderer(window);
        gameScenes->prepareScenes(*renderer);

        srand((unsigned)time(NULL));
        HighPrecisionTimer timer;

        while (window->isOpen())
        {
            Scene * current = gameScenes->getCurrent();
            timer.start();

            SDL_Event e;
            while (SDL_PollEvent(&e) != NULL)
            {
                if (e.type == SDL_QUIT)
                {
                    window->close();
                    break;
                }

                if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
                {
                    int w = 0;
                    int h = 0;

                    SDL_GetWindowSize(window->getWindow(), &w, &h);

                    e.motion.x *= ((float)1920 / w);
                    e.motion.y *= ((float)1080 / h);
                }

                current->onEvent((*gameScenes), &e);
            }

            renderer->clear(window);

            EventManager::get()->performChecks();
            current->onUpdate(*gameScenes, *renderer);
            current->onRender(*renderer);
            renderer->swap();
            timer.stop();

            while (timer.elapsed(NS) < (float)(1.0e9 / window->getRefreshRate()));
        }
    }

    cleanupFunc(bank);
}

void Game::createWindow(int x, int y, int w, int h)
{
    if (window == nullptr)
    {
        window = new Window();
        window->setPosition(x, y);
        window->setSize(w, h);
    }
    else
    {
        throw Error(WINDOW, "Error multiple windows are not supported", WILLIAM);
    }
}

SceneManager* Game::getSceneManager()
{
    return gameScenes;
}

Bank* Game::getGameBank()
{
    return bank;
}