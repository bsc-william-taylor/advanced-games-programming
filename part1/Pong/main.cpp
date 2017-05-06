
#include "Framework.h"
#include "Scenes.h"

void onGameStart(Game& game, Bank * bank, SceneManager * scenes)
{
    StatisticsFile stats;
    bank->pushItem(new Music("data/click.wav", 25), "mouse_click_music");
    bank->pushItem(&stats, "save_file");

    scenes->setScene(MENU);
    scenes->putScenes({
        new OnlinePlayerMap(bank),
        new OnePlayerMap(bank),
        new TwoPlayerMap(bank),
        new Multiplayer(bank),
        new Statistics(bank),
        new Controls(bank),
        new Gameover(bank),
        new About(bank),
        new Menu(bank),
    });

    game.createWindow(CENTER_X, CENTER_Y, 1920, 1080);
    game.begin(RELEASE_DEPLOY, [](Bank* bank) {
        delete bank->popItem<Music>("mouse_click_music");
    });
}