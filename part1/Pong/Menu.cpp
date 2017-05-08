
#include "Scenes.h"
#include "Menu.h"

Menu::Menu(Bank * bank)
{
    title.create(font, "Traditional Pong", 250);
    title.setPosition(1920 / 2, 150, Alignment::CENTER);

    version.create(font, VERSION_STRING, 50);
    version.setPosition(20, 1030, Alignment::RIGHT);

    this->bank = bank;
}

Menu::~Menu()
{
}

void Menu::onRender(Renderer& renderer)
{
    renderer.renderTexture(&background);
    renderer.renderLabel(&version);
    renderer.renderLabel(&title);
    renderer.renderButton(&multiplayer);
    renderer.renderButton(&play1);
    renderer.renderButton(&play2);
    renderer.renderButton(&about);
    renderer.renderButton(&stats);
    renderer.renderButton(&exit);
}

void Menu::onLoad(SceneManager&, Renderer& renderer)
{
    background.create(&renderer, "data/background.png");
    background.setPosition(0, 0, 1920, 1080);

    click = bank->popItem<Music>("mouse_click_music");

    stats.createL(font, "Statistics", 50);
    stats.setPosition(1700, 950, 200, 200);
    stats.onClick(this);

    multiplayer.createL(font, "Multiplayer", 100);
    multiplayer.setPosition(1920 / 2 - 100, 445, 200, 100);
    multiplayer.onClick(this);

    play1.createL(font, "1 Player", 100);
    play1.setPosition(1920 / 2 - 275, 325, 200, 100);
    play1.onClick(this);

    play2.createL(font, "2 Player", 100);
    play2.setPosition(1920 / 2 + 110, 325, 200, 100);
    play2.onClick(this);

    about.createL(font, "Credits", 100);
    about.setPosition(1920 / 2 - 100, 565, 200, 100);
    about.onClick(this);

    exit.createL(font, "Exit", 100);
    exit.setPosition(1920 / 2 - 100, 685, 200, 100);
    exit.onClick(this);
}

void Menu::onActivated(void * data)
{
    StatisticsFile * save_file = bank->popItem<StatisticsFile>("save_file");
    Button * clickedButton = static_cast<Button *>(data);

    if (clickedButton == &exit)
    {
        SDL_Event event;
        event.type = SDL_QUIT;
        SDL_PushEvent(&event);
    }

    if (clickedButton == &play1)
    {
        Controls * scene = static_cast<Controls *>(sceneManager->getScene(CONTROLS));
        scene->setNextState(ONE_PLAYER);
        sceneManager->setScene(CONTROLS);
        save_file->getData().times++;
    }

    if (clickedButton == &play2)
    {
        Controls * scene = static_cast<Controls *>(sceneManager->getScene(CONTROLS));
        scene->setNextState(TWO_PLAYER);
        sceneManager->setScene(CONTROLS);
        save_file->getData().times++;
    }

    if (clickedButton == &about)
    {
        sceneManager->setScene(ABOUT);
    }

    if (clickedButton == &stats)
    {
        sceneManager->setScene(STATS);
    }

    if (clickedButton == &multiplayer)
    {
        sceneManager->setScene(MULTIPLAYER);
    }

    click->play(0);
}

void Menu::onUpdate(SceneManager& scenes, Renderer&)
{
    sceneManager = &scenes;
}

void Menu::onEvent(SceneManager&, SDL_Event * e)
{
    if (e->key.type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
    {
        e->type = SDL_QUIT;
        SDL_PushEvent(e);
    }

    multiplayer.onEvent(e);
    about.onEvent(e);
    stats.onEvent(e);
    play1.onEvent(e);
    play2.onEvent(e);
    exit.onEvent(e);
}
