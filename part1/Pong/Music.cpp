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
#include "Music.h"

// Constructor & Deconstructor
Music::Music(const char * f, unsigned int v)
{
	grab(f);
	vol(v);
}

Music::Music()
{
}

Music::~Music()
{
	if(rawData != NULL) {
		Mix_FreeChunk(rawData);
		rawData = NULL;
	}
}

// Grabs a audio file from disk and loads it
Music& Music::grab(std::string filename)
{
	// grab the raw data
	rawData = Mix_LoadWAV(filename.c_str());
	
	// if we cant load
	if(rawData == NULL)
	{
		// throw an exception
		throw Error(AUDIO, "Couldnt load audio file", WILLIAM);
	}

	// return a reference to the function for multiple calls on one line
	return(*this);
}

// Sets the volume for the music clip
Music& Music::vol(unsigned v) 
{
	// if we have loaded a music clip
	if(rawData != NULL) 
	{
		// set the volume of this chunk
		Mix_VolumeChunk(rawData, v);
	} 
	else 
	{
		// else throw an exception
		throw Error(AUDIO, "Attempted to set the volume of a sound not loaded", WILLIAM);
	}

	// return a reference to the function for multiple calls on one line
	return(*this);
}

// Plays the sound a certain number of times
Music& Music::play(int times)
{
	// if we have loaded a music clip
	if (rawData != NULL)
	{
		// play the audio through the default speakers
		Mix_PlayChannel(-1, rawData, times);
	}
	else
	{
		// else throw an exception
		throw Error(AUDIO, "Attempted to set the volume of a sound not loaded", WILLIAM);
	}

	// return a reference to the function for multiple calls on one line
	return(*this);
}
