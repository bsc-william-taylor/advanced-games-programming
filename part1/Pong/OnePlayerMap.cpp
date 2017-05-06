
#include "Scenes.h"
#include "OnePlayerMap.h"
#include "AiBehaviour.h"

OnePlayerMap::OnePlayerMap(Bank * bank)
{
    this->bank = bank;
}

OnePlayerMap::~OnePlayerMap()
{
    SAFE_RELEASE(ball);
}

void OnePlayerMap::onRender(Renderer& renderer)
{
    renderer.renderTexture(&background);
    player1.render();
    player2.render();
    ball->render();

    hud.render(renderer);
}

void OnePlayerMap::onLoad(SceneManager& mgr, Renderer& renderer)
{
    background.create(&renderer, "data/map.png");
    background.setPosition(0, 0, 1920, 1080);

    ball = new Ball(&renderer, bank);
    hud.create(renderer);

    player1.load(0, renderer);
    player1.setBehaviour(new AiBehaviour(ball));

    player2.load(1, renderer);
    player2.setBehaviour(new PlayerBehaviour(15, true));

    ball->setDirectionSpeed(90, 20, -20);
    ball->create(&mgr, &player1, &player2);
    click = bank->popItem<Music>("mouse_click_music");
}

void OnePlayerMap::onUpdate(SceneManager& scenes, Renderer&)
{
    player1.update();
    player2.update();
    ball->update();
    hud.update();
}

void OnePlayerMap::onEnter()
{
    player1.update();
    player2.update();
    ball->reset();
    ball->showBall();
    hud.enter();
}

void OnePlayerMap::onEvent(SceneManager& scenes, SDL_Event * e)
{
    if (e->key.type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
    {
        scenes.setScene(MENU);
    }

    player1.event(*e);
    player2.event(*e);
}
