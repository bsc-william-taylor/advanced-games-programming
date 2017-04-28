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

#pragma once

#include "Framework.h"

#include <vector>
#include <string>

// some global font settings
global_string filename = "data/statistics.xml";
global_string font = "data/MOZART_0.ttf";

// the data we will want to store in our file
struct StatisticsData {
	int bounces;
	int times;
};

// a class that makes writting a stats file easy
class StatisticsFile 
{
private:
	// the data to write
	StatisticsData data;
	// the XML_File that we will create on disk
	XML_File * file;
public:
	// Constructor & Deconstructor
	StatisticsFile();
	~StatisticsFile();

	// returns a reference to the data
	StatisticsData& getData();
	// writes the new data to the file
	void write();
	// reads the old data from the file
	void read();
};
