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

#include "Framework.h"

// entry point for the application which is defined by the framework
int main(int argc, char * argv[])
{
	// Create the game object
	Game game;

	// cover the entire game in a try block
	try 
	{
		// call the users main function
		onGameStart(game, game.getGameBank(), game.getSceneManager());
	} 
	catch (Error e) 
	{
		// Show an error for the user
		SDL_ShowSimpleMessageBox(NULL,
			e.title(),
			e.what(),
			NULL
			);

		// return 2 on failure
		return EXIT_FAILURE;
	}

	// return 1 on success
	return EXIT_SUCCESS;
}
