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

#include "Exception.h"

// Constructor & Deconstructor
Error::Error(SYSTEM_ERROR sys, std::string msg, SYSTEM_PROGRAMMER user)
{
	// set all the variables for the class
	systemErrorLocation = sys;
	ErrorsOwner = user;
	error_message = msg;
}

Error::~Error() throw()
{
}

// returns the message
const char * Error::what()
{
	// create the message
	static std::string message = "Error thrown by ";

	// append the person that programmed that error into the message
	switch (ErrorsOwner)
	{
		case WILLIAM: message += " William Taylor\n\nMessage ->";
			break;
	}

	// append the users message to the message
	message.append(error_message.c_str());
	// return it to the function
	return(message.c_str());
}

const char * Error::title()
{
	/// calculate the title for the error window
	static std::string title = "Error !!!";

	// set the title based on error type
	switch (systemErrorLocation)
	{
		case NETWORKING: title = "Networking error";
			break;
		case RENDERER: title = "Renderer error";
			break;
		case TEXTURE: title = "Texture error";
			break;
		case FILE_IO: title = "File_IO error";
			break;
		case WINDOW: title = "Window error";
			break;
		case AUDIO: title = "Audio error";
			break;
		case LABEL: title = "Label error";
			break;
		case GAME: title = "Game error";
			break;
	}

	// return the title as a const char * (c style string)
	return(title.c_str());
}
