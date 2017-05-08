
#include "HighPrecisionTimer.h"
#include "System.h"

OperatingSystem::OperatingSystem()
    : sceneManager(&windowManager)
{
}

OperatingSystem::~OperatingSystem()
{
}

bool OperatingSystem::setupLibraries()
{
    bool setupSuccess = true;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        setupSuccess = false;
    }

    int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;

    if (IMG_Init(flags) != flags)
    {
        setupSuccess = false;
    }

    if (TTF_Init() == -1)
    {
        setupSuccess = false;
    }

    srand((unsigned)time(NULL));
    FreeImage_Initialise();
    return setupSuccess;
}

bool OperatingSystem::meetsMinimumSpecification()
{
    return (GPU(false).has(GraphicsApi::OpenGL, 3.3));
}

void OperatingSystem::releaseLibraries()
{
    FreeImage_DeInitialise();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void OperatingSystem::executeProgram()
{
    HighPrecisionTimer frameTimer;

    SDL_Event operatingSystemEvents;
    SDL_bool run = SDL_TRUE;

    GPU gpu(true);

    if (meetsMinimumSpecification())
    {
        sceneManager.createScenes();

        while (run)
        {
            frameTimer.start();

            while (SDL_PollEvent(&operatingSystemEvents))
            {
                if (operatingSystemEvents.type == SDL_QUIT)
                {
                    run = SDL_FALSE;
                    break;
                }
                else
                {
                    sceneManager.handeEventScene(operatingSystemEvents);
                }
            }

            sceneManager.updateScene();
            sceneManager.renderScene();

            windowManager.swapBuffers();

            while (frameTimer.elapsed(TimeType::Nanoseconds) <= (float)(1.0e9 / 60.00F));
        }
    }
}

Window& OperatingSystem::acquireWindow()
{
    return windowManager;
}

AssetManager * OperatingSystem::acquireAssetManager()
{
    return &assetManager;
}

SceneManager * OperatingSystem::acquireSceneManager()
{
    return &sceneManager;
}

int main(int argc, char ** argv)
{
    int message = EXIT_SUCCESS;

    try
    {
        OperatingSystem system;

        if (system.setupLibraries())
        {
            onApplicationStart(&system);
            system.releaseLibraries();
        }
        else
        {
            message = EXIT_FAILURE;
        }
    }
    catch (Error e)
    {
        message = EXIT_FAILURE;

        SDL_ShowSimpleMessageBox(NULL,
            e.title(),
            e.what(),
            NULL
        );
    }

    return message;
}