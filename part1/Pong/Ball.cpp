
#include "ScreenCollision.h"
#include "Ball.h"
#include "Screen.h"

Ball::Ball(Renderer * r, Bank * b)
{
    position.resize(1);
    renderer = r;
    show = false;
    bank = b;

    behaviour = new BallBehaviour(this, &sprite);
}

Ball::~Ball()
{
    delete(behaviour);
}

BallBehaviour * Ball::getBehaviour()
{
    return(behaviour);
}

std::vector<SDL_Rect>& Ball::getPosition()
{
    return(position);
}

void Ball::setDirectionSpeed(int d, int x, int y)
{
    behaviour->setup(d, x, y);
}

SDL_Rect& Ball::getClickRegion()
{
    return(sprite.getPosition());
}

void Ball::update()
{
    if (show) {
        actor.updateBehaviours();
    }
}

void Ball::setPosition(int x, int y)
{
    position[0].x = x;
    position[0].y = y;
}

void Ball::create(SceneManager * mgr, Player * player1, Player * player2)
{
    sprite.create(renderer, "data/bar.png");
    sprite.setPosition(935, 521, 50, 50);

    actor.pushBehaviour(behaviour);

    listener.pushObjects(this, &screen, new ScreenCollision(mgr, bank->popItem<StatisticsFile>("save_file")));
    player1_Collision.pushObjects(this, player1, new BlockCollision());
    player2_Collision.pushObjects(this, player2, new BlockCollision());

    EventManager::get()->pushEventEntry(&player1_Collision);
    EventManager::get()->pushEventEntry(&player2_Collision);
    EventManager::get()->pushEventEntry(&listener);

    position[0] = sprite.getPosition();
}

void Ball::hideBall()
{
    show = false;
}

void Ball::showBall()
{
    show = true;
}

void Ball::reset()
{
    sprite.setPosition(935, 521, 50, 50);
    position[0] = sprite.getPosition();
    behaviour->reset();
}

void Ball::render()
{
    if (show) {
        renderer->renderTexture(&sprite);
    }
}
