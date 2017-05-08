
#pragma once

#include "Framework.h"
#include "Resources.h"
#include "Player.h"
#include "Music.h"
#include "Ball.h"

class Menu : public Scene, public IHandler
{
    SceneManager* sceneManager;
    Texture background;
    Music* click;
    Bank* bank;

    Button multiplayer;
    Button stats;
    Button about;
    Button play1;
    Button play2;
    Button exit;

    Label version;
    Label title;
public:
    Menu(Bank *);
    ~Menu();

    void onRender(Renderer& renderer);
    void onLoad(SceneManager&, Renderer& renderer);
    void onUpdate(SceneManager&, Renderer&);
    void onEvent(SceneManager&, SDL_Event *);
    void onActivated(void *);
};
