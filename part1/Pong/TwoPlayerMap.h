
#pragma once

#include "Framework.h"
#include "Resources.h"
#include "Ball.h"
#include "Player.h"
#include "Hud.h"

class TwoPlayerMap : public Scene
{
    Texture background;
    Player player1;
    Player player2;
    Display hud;

    Music* click;
    Ball* ball;
    Bank* bank;
public:
    TwoPlayerMap(Bank *);
    ~TwoPlayerMap();

    void onEvent(SceneManager&, SDL_Event *);
    void onUpdate(SceneManager&, Renderer&);
    void onLoad(SceneManager&, Renderer&);
    void onRender(Renderer&);
    void onEnter();
};
