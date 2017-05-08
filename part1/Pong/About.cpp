
#include "Scenes.h"

About::About(Bank * bank)
{
    this->bank = bank;
}

About::~About()
{
}

void About::onRender(Renderer& renderer)
{
    renderer.renderTexture(&background);
    renderer.renderLabel(&title);
    renderer.renderButton(&exit);
    renderer.renderLabel(&email);

    paragraph.render(renderer);
}

void About::onLoad(SceneManager&, Renderer& renderer)
{
    background.create(&renderer, "data/background.png");
    background.setPosition(0, 0, 1920, 1080);

    title.create(font, "Credits", 150);
    title.setPosition(1920 / 2, 150, Alignment::CENTER);

    exit.createL(font, "Back", 100);
    exit.setPosition(50, 0, 200, 200);
    exit.onClick(this);

    paragraph.setPosition(1920 / 2, 300, Alignment::CENTER);
    paragraph.setup(50, "data/about.xml", "about");

    email.create(font, "wi11berto@yahoo.co.uk", 30);
    email.setPosition(20, 1030, Alignment::RIGHT);

    click = bank->popItem<Music>("mouse_click_music");
}

void About::onActivated(void * data)
{
    Button* clickedButton = static_cast<Button *>(data);

    if (clickedButton == &exit)
    {
        sceneManager->setScene(MENU);
    }

    click->play(0);
}

void About::onUpdate(SceneManager& scenes, Renderer&)
{
    sceneManager = &scenes;
}

void About::onEvent(SceneManager& scenes, SDL_Event * e)
{
    if (e->key.type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
    {
        scenes.setScene(MENU);
    }

    exit.onEvent(e);
}
