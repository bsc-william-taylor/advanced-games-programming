/**
 * 
 * Copyright (c) 2014 : William Taylor : wi11berto@yahoo.co.uk
 *  
 * This software is provided 'as-is', without any 
 * express or implied warranty. In no event will 
 * the authors be held liable for any damages 
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose, 
 * including commercial applications, and to alter it and redistribute 
 * it freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; 
 *    you must not claim that you wrote the original software. 
 *    If you use this software in a product, an acknowledgment 
 *    in the product documentation would be appreciated but 
 *    is not required.
 * 
 * 2. Altered source versions must be plainly marked as such, 
 *    and must not be misrepresented as being the original software.
 *  
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "ScreenCollision.h"
#include "ResetEvent.h"
#include "Scenes.h"
#include "Hud.h"

// Constructor & Deconstructor
ScreenCollision::ScreenCollision(SceneManager * scenes,  StatisticsFile * stats)
	: timeoutListener(TimeoutListener(new Reset_Event(this), BALL_RESET_DELAY)),
	  clip(Music("data/plop.wav", 50))
{
	this->timeoutListener.disable();
	this->triggered = false;
	this->stats = stats;
	this->mgr = scenes;
	
	EventManager::get()->PushEventEntry(&timeoutListener);
}

ScreenCollision::~ScreenCollision()
{
}

// reset the game for the next point to be played
void ScreenCollision::restart()
{
	// get the gameover scene and the current scene
	Gameover * gameOverScene = static_cast<Gameover *>(mgr->getScene(GAMEOVER));
	Scene * currentScene = mgr->getCurrent();

	// if we are on 1 player or 2 player mode
	if (currentScene != mgr->getScene(ONLINE_PLAYER_MAP)) 
	{
		// if player 1 wins
		if (Display::player1 == POINTS_TO_WIN)
		{
			// if we are on player 1 mode
			if (currentScene == mgr->getScene(ONE_PLAYER)) 
				gameOverScene->setString("Ai Wins");		// set the winner text to be ai wins
			// else
			if (currentScene == mgr->getScene(TWO_PLAYER))
				gameOverScene->setString("Player 1 Wins");	// set the winner text to be player 1 wins
		}

		// if player 1 wins
		if (Display::player2 == POINTS_TO_WIN)
		{
			// if we are on player 2 mode
			if (currentScene == mgr->getScene(TWO_PLAYER)) 
				gameOverScene->setString("Player 2 Wins");	// set the winner text to be player 2 wins
			// else
			if (currentScene == mgr->getScene(ONE_PLAYER))
				gameOverScene->setString("Player Wins");	// set the winner text to be player 1 wins
		}
	} 
	else 
	{
		if (Display::player1 == POINTS_TO_WIN)
			gameOverScene->setString("Player 1 Wins");
		if (Display::player2 == POINTS_TO_WIN)
			gameOverScene->setString("Player 2 Wins");
	}

	// if someone has actually won go to the game over scene
	if (Display::player1 == POINTS_TO_WIN || Display::player2 == POINTS_TO_WIN)
		mgr->setScene(GAMEOVER);

	// reset the event and the game ball
	triggered = false;
	ball->reset();
}

// handle when the ball comes in contact with the screen boundries
void ScreenCollision::onActivated(void * data)  {
	// get the collision data
	CollisionData * info = static_cast<CollisionData *>(data);
	// get the event manager
	EventManager * eventManager = EventManager::get();
	// get the ball
	ball = static_cast<Ball *>(info->one);
	// and get the balls behaviour
	BallBehaviour * bv = ball->getBehaviour();
	
	// if it hasnt been trigered before play the sound
	if (!triggered)
		clip.play(0);

	// now calculate the appropiate response based on collision point
	switch (info->INDEX_2)
	{
		// if we hit the right hand side of the screen
		case Screen::RIGHT: 
		{
			// if we havent been triggered
			if(!triggered) 
			{
				// make the timer active & increment player 1's points
				timeoutListener.makeActive();
				stats->getData().bounces++;
			    Display::player1++;
				triggered = true;
			}

			break;
		}

		case Screen::LEFT: 
		{
			// if we havent been triggered
			if(!triggered) 
			{
				// make the timer active & increment player 2's points
				timeoutListener.makeActive();
				stats->getData().bounces++;
				Display::player2++;
				triggered = true;
			}

			break;
		}

		// else
		default:
		{
			// increase the bounces and negate the y
			stats->getData().bounces++;
			bv->negateY();
			break;
		}
	}
}
