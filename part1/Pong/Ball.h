
#pragma once

#include "CollisionListener.h"
#include "BlockCollision.h"
#include "BallBehaviour.h"
#include "Resources.h"
#include "Framework.h"
#include "Player.h"

class Ball : public ICollidable
{
    BallBehaviour* behaviour;
    ActorPosition position;
    Texture sprite;
    Screen screen;
    Actor actor;
    Bank * bank;

    Collision player1_Collision;
    Collision player2_Collision;
    Collision listener;
    Renderer * renderer;
    bool show;
public:
    Ball(Renderer *, Bank *);
    ~Ball();

    BallBehaviour* getBehaviour();
    ActorPosition& getPosition();
    SDL_Rect& getClickRegion();

    void create(SceneManager *, Player *, Player *);
    void setDirectionSpeed(int, int, int);
    void setPosition(int, int);
    void hideBall();
    void showBall();
    void update();
    void render();
    void reset();
};
