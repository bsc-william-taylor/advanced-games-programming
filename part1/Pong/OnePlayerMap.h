
#pragma once

#include "Framework.h"
#include "Resources.h"
#include "Ball.h"
#include "Player.h"
#include "Hud.h"

class OnePlayerMap : public Scene
{
	Texture background;
	Player player2;
	Player player1;
	Display hud;
	Ball* ball;
    Music* click;
    Bank* bank;
public:
	OnePlayerMap(Bank *);
	~OnePlayerMap();

	void onEvent(SceneManager&, SDL_Event *);
	void onUpdate(SceneManager&, Renderer&);
	void onLoad(SceneManager&, Renderer&);
	void onRender(Renderer&);
	void onEnter();
};
