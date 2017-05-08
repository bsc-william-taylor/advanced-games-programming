
#include "ScreenCollision.h"
#include "ResetEvent.h"
#include "Scenes.h"
#include "Hud.h"

const int BallResetDelay = 1500;
const int PointsToWin = 10;

ScreenCollision::ScreenCollision(SceneManager * scenes, StatisticsFile * stats) :
    timeoutListener(new GameResetEvent(this), BallResetDelay),
    clip(Music("data/plop.wav", 50))
{
    this->timeoutListener.disable();
    this->triggered = false;
    this->stats = stats;
    this->mgr = scenes;

    EventManager::get()->pushEventEntry(&timeoutListener);
}

ScreenCollision::~ScreenCollision()
{
}

void ScreenCollision::restart()
{
    auto gameOverScene = static_cast<Gameover *>(mgr->getScene(GAMEOVER));
    auto currentScene = mgr->getCurrent();

    if (currentScene != mgr->getScene(ONLINE_PLAYER_MAP))
    {
        if (Display::player1 == PointsToWin)
        {
            if (currentScene == mgr->getScene(ONE_PLAYER))
                gameOverScene->setString("Ai Wins");
            if (currentScene == mgr->getScene(TWO_PLAYER))
                gameOverScene->setString("Player 1 Wins");
        }

        if (Display::player2 == PointsToWin)
        {
            if (currentScene == mgr->getScene(TWO_PLAYER))
                gameOverScene->setString("Player 2 Wins");
            if (currentScene == mgr->getScene(ONE_PLAYER))
                gameOverScene->setString("Player Wins");
        }
    }
    else
    {
        if (Display::player1 == PointsToWin)
            gameOverScene->setString("Player 1 Wins");
        if (Display::player2 == PointsToWin)
            gameOverScene->setString("Player 2 Wins");
    }

    if (Display::player1 == PointsToWin || Display::player2 == PointsToWin)
        mgr->setScene(GAMEOVER);

    triggered = false;
    ball->reset();
}

void ScreenCollision::onActivated(void * data)
{
    CollisionData* info = static_cast<CollisionData *>(data);
    EventManager* eventManager = EventManager::get();
    ball = static_cast<Ball *>(info->objectOne);
    BallBehaviour* bv = ball->getBehaviour();

    if (!triggered)
        clip.play(0);

    switch ((ScreenSide)info->indexTwo)
    {
        case ScreenSide::RIGHT:
        {
            if (!triggered)
            {
                timeoutListener.makeActive();
                stats->getData().bounces++;
                Display::player1++;
                triggered = true;
            }

            break;
        }

        case ScreenSide::LEFT:
        {
            if (!triggered)
            {
                timeoutListener.makeActive();
                stats->getData().bounces++;
                Display::player2++;
                triggered = true;
            }

            break;
        }

        default:
        {
            stats->getData().bounces++;
            bv->negateY();
            break;
        }
    }
}
