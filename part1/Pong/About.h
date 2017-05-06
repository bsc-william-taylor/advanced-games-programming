
#pragma once

#include "Framework.h"
#include "Resources.h"
#include "Paragraph.h"
#include "Player.h"
#include "Ball.h"

class About : public Scene, public IHandler
{
    SceneManager* sceneManager;
    Music* click;
    Bank* bank;

    Paragraph paragraph;
    Texture background;
    Button exit;
    Label email;
    Label title;
public:
    About(Bank *);
    ~About();

    void onRender(Renderer& renderer);
    void onLoad(SceneManager&, Renderer& renderer);
    void onUpdate(SceneManager&, Renderer&);
    void onEvent(SceneManager&, SDL_Event *);
    void onActivated(void *);
};
