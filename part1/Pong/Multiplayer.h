
#pragma once

#include "Framework.h"
#include "Resources.h"
#include "Player.h"
#include "Music.h"
#include "Ball.h"

class Multiplayer : public Scene, public IHandler
{
private:
    SceneManager* sceneManager;
    Music* click;
    Bank* bank;
    Texture background;
    Button player1, player2;
    Label servername, hostname, title;
    std::string name;
public:
    Multiplayer(Bank *);
    ~Multiplayer();

    void onRender(Renderer& renderer);
    void onLoad(SceneManager&, Renderer& renderer);
    void onUpdate(SceneManager&, Renderer&);
    void onEvent(SceneManager&, SDL_Event *);
    void onActivated(void *);
    void onEnter();
    void onExit();
};
