
#include "Controls.h"
#include "Scenes.h"

Controls::Controls(Bank * bank)
{
    this->bank = bank;
}

Controls::~Controls()
{
}

void Controls::onRender(Renderer& renderer)
{
    renderer.renderTexture(&background);
    renderer.renderLabel(&title);
    renderer.renderLabel(&controls1);
    renderer.renderLabel(&controls2);
    renderer.renderLabel(&controls3);
    renderer.renderLabel(&controls4);
    renderer.renderButton(&play);
}

void Controls::onLoad(SceneManager&, Renderer& renderer)
{
    background.create(&renderer, "data/background.png");
    background.setPosition(0, 0, 1920, 1080);

    title.create(font, "Controls", 150);
    title.setPosition(1920 / 2, 150, Alignment::CENTER);

    controls1.create(font, "W Key = Up", 125);
    controls1.setPosition(500, 400, Alignment::CENTER);
    controls2.create(font, "S Key = Down", 125);
    controls2.setPosition(500, 600, Alignment::CENTER);

    controls3.create(font, "Arrow Up = Up", 125);
    controls3.setPosition(1400, 400, Alignment::CENTER);
    controls4.create(font, "Arrow Down = Down", 125);
    controls4.setPosition(1400, 600, Alignment::CENTER);

    this->click = bank->popItem<Music>("mouse_click_music");

    play.createL(font, "Continue", 100);
    play.setPosition(860, 700, 200, 200);
    play.onClick(this);
}

void Controls::onActivated(void * data)
{
    Button * clickedButton = static_cast<Button *>(data);

    click->play(0);

    if (&play == clickedButton)
    {
        sceneManager->setScene(nextScene);
    }
}

void Controls::setNextState(int ID)
{
    this->nextScene = ID;
}

void Controls::onUpdate(SceneManager& scenes, Renderer&)
{
    sceneManager = &scenes;
}

void Controls::onEvent(SceneManager& scenes, SDL_Event * e)
{
    if (e->key.type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
    {
        scenes.setScene(MENU);
    }

    play.onEvent(e);
}
