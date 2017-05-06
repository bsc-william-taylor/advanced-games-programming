
#include "ScreenCollision.h"
#include "ResetEvent.h"

GameResetEvent::GameResetEvent(ScreenCollision * e)
    : event(e)
{
}

GameResetEvent::~GameResetEvent()
{
}

void GameResetEvent::onActivated(void* data)
{
    event->restart();
}