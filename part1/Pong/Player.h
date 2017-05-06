
#pragma once

#include "CollisionListener.h"
#include "ICollidable.h"
#include "PlayerBehavior.h"
#include "Resources.h"
#include "Framework.h"
#include "Screen.h"

enum PLAYER_TYPE {
    PLAYER_ONE,
    PLAYER_TWO
};

class Player : public ICollidable
{
    ActorPosition positions;
    Texture sprites;
    Renderer* renderer;
    Actor actor;
public:
    Player();
    ~Player();

    ActorPosition& getPosition();
    Texture* getTexture();

    void setBehaviour(Behaviour *);
    void setPosition(int, int);
    void load(int, Renderer&);
    void event(SDL_Event&);
    void render();
    void update();
    void clear();

    std::string getPositionAsString();
};
