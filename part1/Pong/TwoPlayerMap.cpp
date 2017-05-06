
#include "Scenes.h"
#include "TwoPlayerMap.h"

TwoPlayerMap::TwoPlayerMap(Bank * bank)
{
    this->bank = bank;
}

TwoPlayerMap::~TwoPlayerMap()
{
    SAFE_RELEASE(ball);
}

void TwoPlayerMap::onRender(Renderer& renderer)
{
    renderer.renderTexture(&background);
    player1.render();
    player2.render();
    ball->render();

    hud.render(renderer);
}

void TwoPlayerMap::onLoad(SceneManager& mgr, Renderer& renderer)
{
    background.create(&renderer, "data/map.png");
    background.setPosition(0, 0, 1920, 1080);
    hud.create(renderer);

    player1.load(PLAYER_ONE, renderer);
    player2.load(PLAYER_TWO, renderer);
    player1.setBehaviour(new PlayerBehaviour(15, false));
    player2.setBehaviour(new PlayerBehaviour(15, true));

    ball = new Ball(&renderer, bank);
    ball->setDirectionSpeed(90, 20, -20);
    ball->create(&mgr, &player1, &player2);

    click = bank->popItem<Music>("mouse_click_music");
}

void TwoPlayerMap::onUpdate(SceneManager& scenes, Renderer&)
{
    player1.update();
    player2.update();
    ball->update();
    hud.update();
}

void TwoPlayerMap::onEnter()
{
    player1.clear();
    player2.clear();
    ball->reset();
    hud.enter();
}

void TwoPlayerMap::onEvent(SceneManager& scenes, SDL_Event * e)
{
    if (e->key.type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
    {
        scenes.setScene(MENU);
    }

    player1.event(*e);
    player2.event(*e);
}
