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
 *
 */

#include "Framework.h"
#include "Scenes.h"

// our main method which is provided by the framework
void onGameStart(Game& game, Bank * bank, SceneManager * scenes)
{
	// create a stats file
	StatisticsFile stats;

	// push 2 items to the asset bank for use accross multiple scenes
	bank->push_item(new Music("data/click.wav", 25), "mouse_click_music");
	bank->push_item(&stats, "save_file");

	// set the menu as the starting point and load the scenes
	scenes->setScene(MENU);
	scenes->putScenes({ 
		new OnlinePlayerMap(bank),
		new OnePlayerMap(bank),
		new TwoPlayerMap(bank),
		new Multiplayer(bank),
		new Statistics(bank),
		new Controls(bank),
		new Gameover(bank),
		new About(bank),
		new Menu(bank),
	});

	// create the window and begin the game, deleting the mouse click when the game is finished
	game.createWindow(CENTER_X, CENTER_Y, 1920, 1080);
	game.begin(RELEASE_DEPLOY, [] (Bank * bank) {
		delete bank->pop_item<Music>("mouse_click_music");
	});
}