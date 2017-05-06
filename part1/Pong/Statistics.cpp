
#include "Scenes.h"

Statistics::Statistics(Bank * bank)
{
    this->bank = bank;

    timesPlayedTitle.create(font, "Times Played", 125);
    bounceTitle.create(font, "Pong Bounces", 125);
    title.create(font, "Statistics", 150);

    timesPlayedTitle.setPosition(1920 / 2 - 500, 500, CENTER);
    bounceTitle.setPosition(1920 / 2 + 500, 500, CENTER);
    title.setPosition(1920 / 2, 150, CENTER);
}

Statistics::~Statistics()
{
}

void Statistics::onRender(Renderer& renderer)
{
    renderer.renderTexture(&background);
    renderer.renderLabel(&timesPlayedTitle);
    renderer.renderLabel(&bounceTitle);
    renderer.renderLabel(&timesPlayed);
    renderer.renderLabel(&bounces);
    renderer.renderLabel(&title);
    renderer.renderButton(&exit);
}

void Statistics::onLoad(SceneManager&, Renderer& renderer)
{
    background.create(&renderer, "data/background.png");
    background.setPosition(0, 0, 1920, 1080);

    statistics = bank->popItem<StatisticsData>("save_file");
    click = bank->popItem<Music>("mouse_click_music");

    exit.createL(font, "Back", 100);
    exit.setPosition(50, 0, 200, 200);
    exit.onClick(this);
}

void Statistics::onActivated(void * data)
{
    Button * clickedButton = static_cast<Button *>(data);

    if (clickedButton == &exit)
    {
        sceneManager->setScene(MENU);
    }

    click->play(0);
}

void Statistics::onUpdate(SceneManager& scenes, Renderer&)
{
    std::string timesPlayedString = to_string(statistics->times);
    std::string bouncesString = to_string(statistics->bounces);

    sceneManager = &scenes;

    if (timesPlayed.getText() != timesPlayedString || bounces.getText() != bouncesString)
    {
        timesPlayed.create(font, timesPlayedString, 200);
        timesPlayed.setPosition(1920 / 2 - 500, 700, CENTER);

        bounces.create(font, bouncesString, 200);
        bounces.setPosition(1920 / 2 + 500, 700, CENTER);
    }
}

void Statistics::onEvent(SceneManager& scenes, SDL_Event * e)
{
    if (e->key.type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
    {
        scenes.setScene(MENU);
    }

    exit.onEvent(e);
}
