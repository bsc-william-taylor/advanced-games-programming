
#pragma once

#include "Framework.h"
#include "Resources.h"
#include "Player.h"
#include "Music.h"
#include "Ball.h"

class Controls : public Scene, public IHandler
{
    SceneManager * sceneManager;
    Texture background;
    Music * click;
    Bank * bank;

    Label title;
    Label controls1;
    Label controls2;
    Label controls3;
    Label controls4;

    unsigned int nextScene;
    Button play;
public:
    Controls(Bank *);
    ~Controls();

    void onRender(Renderer& renderer);
    void onLoad(SceneManager&, Renderer& renderer);
    void onUpdate(SceneManager&, Renderer&);
    void onEvent(SceneManager&, SDL_Event *);
    void onActivated(void *);
    void setNextState(int);
};
