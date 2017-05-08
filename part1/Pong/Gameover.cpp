
#include "Gameover.h"
#include "Scenes.h"

Gameover::Gameover(Bank * bank)
{
    this->bank = bank;
}

Gameover::~Gameover()
{
}

void Gameover::onRender(Renderer& renderer)
{
    renderer.renderTexture(&background);
    renderer.renderLabel(&title);
    renderer.renderLabel(&winner);
    renderer.renderLabel(&score1);
    renderer.renderLabel(&score2);
    renderer.renderButton(&exit);
}

void Gameover::onLoad(SceneManager&, Renderer& renderer)
{
    background.create(&renderer, "data/background.png");
    background.setPosition(0, 0, 1920, 1080);

    title.create(font, "Game Over", 150);
    title.setPosition(1920 / 2, 150, Alignment::CENTER);

    exit.createL(font, "Back", 100);
    exit.setPosition(50, 0, 200, 200);
    exit.onClick(this);

    winner.create(font, " ", 75);
    winner.setPosition(1920 / 2, 500, Alignment::CENTER);

    score2.create(font, " ", 175);
    score1.create(font, " ", 175);
    score2.setPosition(1670, 500, Alignment::CENTER);
    score1.setPosition(250, 500, Alignment::CENTER);

    click = bank->popItem<Music>("mouse_click_music");
}

void Gameover::setString(const char * str)
{
    this->winnerString = str;
}

void Gameover::onActivated(void * data)
{
    Button* clickedButton = static_cast<Button *>(data);

    if (clickedButton == &exit)
    {
        sceneManager->setScene(MENU);
    }

    click->play(0);
}

void Gameover::onUpdate(SceneManager& scenes, Renderer&)
{
    std::string player1ScoreString = to_string(Display::player1);
    std::string player2ScoreString = to_string(Display::player2);

    sceneManager = &scenes;

    if (winner.getText() != winnerString || score1.getText() != player1ScoreString || score2.getText() != player2ScoreString)
    {
        score2.create(font, player2ScoreString, 175);
        score1.create(font, player1ScoreString, 175);
        winner.create(font, winnerString, 200);

        winner.setPosition(1920 / 2, 500, Alignment::CENTER);
        score2.setPosition(1670, 500, Alignment::CENTER);
        score1.setPosition(250, 500, Alignment::CENTER);
    }
}

void Gameover::onEvent(SceneManager&, SDL_Event * e)
{
    exit.onEvent(e);
}
