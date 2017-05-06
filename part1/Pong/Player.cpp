
#include "EventManager.h"
#include "Player.h"

Player::Player()
{
}

Player::~Player()
{

}

void Player::render()
{
    renderer->renderTexture(&sprites);
}

Texture * Player::getTexture()
{
    return &sprites;
}

void Player::setBehaviour(Behaviour * beh)
{
    beh->onAccept(this);
    actor.pushBehaviour(beh);
}

std::string Player::getPositionAsString()
{
    std::string str = "";

    str += to_string(sprites.getPosition().x);
    str += ":";
    str += to_string(sprites.getPosition().y);

    return str;
}

void Player::setPosition(int x, int y)
{
    sprites.setPosition(x, y, 20, 200);
    positions.clear();
    positions.push_back(sprites.getPosition());
}

ActorPosition& Player::getPosition()
{
    positions.clear();
    positions.push_back(sprites.getPosition());

    return(positions);
}

void Player::event(SDL_Event& e)
{
    actor.notifyBehaviours(e);
}

void Player::clear()
{
    //keys.clear();
}

void Player::update()
{
    actor.updateBehaviours();
}

void Player::load(int i, Renderer& renderer)
{
    this->renderer = &renderer;

    SDL_Rect rect[2] = {
        { 50,   490,  20,  200 },
        { 1870, 490,  20,  200 }
    };

    sprites.create(this->renderer, "data/bar.png");
    sprites.setPosition(rect[i].x, rect[i].y, rect[i].w, rect[i].h);
}
