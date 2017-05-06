
#pragma once

#include "Framework.h"
#include "Resources.h"
#include "Player.h"
#include "Ball.h"

class Statistics : public Scene, public IHandler
{
    StatisticsData* statistics;
    SceneManager* sceneManager;
    Music* click;
    Bank* bank;

    Label timesPlayedTitle;
    Label timesPlayed;
    Label bounceTitle;
    Label bounces;
    Label title;

    Texture background;
    Button exit;
public:
    Statistics(Bank * bank);
    ~Statistics();

    void onUpdate(SceneManager& sceneManager, Renderer& renderer);
    void onEvent(SceneManager& sceneManager, SDL_Event* sdl_event);
    void onLoad(SceneManager& sceneManager, Renderer& renderer);
    void onRender(Renderer& renderer);
    void onActivated(void * data);
};
