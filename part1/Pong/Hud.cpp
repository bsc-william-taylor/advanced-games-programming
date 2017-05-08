
#include "Hud.h"

int Display::player1 = 0;
int Display::player2 = 0;

Display::Display()
{
}

Display::~Display()
{
}

void Display::render(Renderer& renderer)
{
    renderer.renderLabel(&playerScoreOne);
    renderer.renderLabel(&playerScoreTwo);
}

void Display::create(Renderer& renderer)
{
    playerScoreOne.create(font, to_string(player1), 200);
    playerScoreTwo.create(font, to_string(player2), 200);

    playerScoreOne.setPosition(1920 / 2, 0, Alignment::LEFT);
    playerScoreTwo.setPosition(1920 / 2, 0, Alignment::RIGHT);
}

void Display::update()
{
    playerScoreOne.create(font, to_string(player1), 200);
    playerScoreTwo.create(font, to_string(player2), 200);

    playerScoreOne.setPosition(1920 / 2 - 115, 100, Alignment::LEFT);
    playerScoreTwo.setPosition(1920 / 2 + 100, 100, Alignment::RIGHT);
}

void Display::enter()
{
    player1 = NULL;
    player2 = NULL;
}
