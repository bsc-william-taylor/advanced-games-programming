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

#include "Resources.h"

// Constructor & Decosntructor
StatisticsFile::StatisticsFile()
	: file(new XML_File(filename, "stats"))
{
	// read the file immediatly
	read();
}

StatisticsFile::~StatisticsFile()
{
	// write the new data
	write();

	// and release the file
	SAFE_RELEASE(file);
}

// This function creates the document
void StatisticsFile::write()
{
	// create a new document
	tinyxml2::XMLDocument doc;

	// create some nodes
	tinyxml2::XMLElement * bounces = doc.NewElement("bounces");
	tinyxml2::XMLElement * stats = doc.NewElement("stats");
	tinyxml2::XMLElement * times = doc.NewElement("times");

	// and insert them into the file
	bounces->InsertEndChild(doc.NewText(to_string(data.bounces).c_str()));
	times->InsertEndChild(doc.NewText(to_string(data.times).c_str()));
	stats->InsertEndChild(bounces);
	stats->InsertEndChild(times);

	// and then save them
	doc.InsertFirstChild(stats);
	doc.SaveFile("data/statistics.xml");
}

// returns the data that will be written to the file
StatisticsData& StatisticsFile::getData()
{
	return(data);
}

// reads the file from the XML file specified in the constructor
void StatisticsFile::read()
{
	data.bounces = atoi(file->getValue("bounces").c_str());
	data.times = atoi(file->getValue("times").c_str());
}
