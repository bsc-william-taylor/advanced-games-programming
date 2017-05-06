
#include "Framework.h"

int main(int argc, char * argv[])
{
    Game game;

    try
    {
        onGameStart(game, game.getGameBank(), game.getSceneManager());
    }
    catch (Error e)
    {
        SDL_ShowSimpleMessageBox(NULL,
            e.title(),
            e.what(),
            NULL
        );

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
