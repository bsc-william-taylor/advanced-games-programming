
#pragma once

#include "Framework.h"
#include "Resources.h"
#include "Networking.h"
#include "Ball.h"
#include "Player.h"
#include "Hud.h"

class OnlinePlayerMap : public Scene
{
    Texture background;
    Player player1;
    Player player2;
    Display hud;

    std::string player_name;
    Client client;
    Server server;
    Music* click;
    Ball* ball;
    Bank* bank;

public:
    OnlinePlayerMap(Bank *);
    ~OnlinePlayerMap();

    void handleClientMessages(std::string);
    void handleServerMessages(std::string);
    void giveDetails(std::string, std::string);
    void onEvent(SceneManager&, SDL_Event *);
    void onUpdate(SceneManager&, Renderer&);
    void onLoad(SceneManager&, Renderer&);
    void onRender(Renderer&);
    void onEnter();
    void onExit();
};
