
#pragma once

#include "Framework.h"
#include "Resources.h"
#include "Player.h"
#include "Ball.h"

class Gameover : public Scene, public IHandler
{
    SceneManager* sceneManager;
    Texture background;
    Button exit;
    Music* click;
    Bank* bank;

    Label winner;
    Label score1;
    Label score2;
    Label title;

    const char * winnerString;
public:
    Gameover(Bank *);
    ~Gameover();

    void onRender(Renderer& renderer);
    void onLoad(SceneManager&, Renderer& renderer);
    void onUpdate(SceneManager&, Renderer&);
    void onEvent(SceneManager&, SDL_Event *);
    void setString(const char *);
    void onActivated(void *);
};
