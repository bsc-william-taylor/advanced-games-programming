
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
    renderer.renderLabel(&playerScore_1);
    renderer.renderLabel(&playerScore_2);
}

void Display::create(Renderer& renderer)
{
    playerScore_1.create(font, to_string(player1), 200);
    playerScore_2.create(font, to_string(player2), 200);

    playerScore_1.setPosition(1920 / 2, 0, LEFT);
    playerScore_2.setPosition(1920 / 2, 0, RIGHT);
}

void Display::update()
{
    playerScore_1.create(font, to_string(player1), 200);
    playerScore_2.create(font, to_string(player2), 200);

    playerScore_1.setPosition(1920 / 2 - 115, 100, LEFT);
    playerScore_2.setPosition(1920 / 2 + 100, 100, RIGHT);
}

void Display::enter()
{
    player1 = NULL;
    player2 = NULL;
}
