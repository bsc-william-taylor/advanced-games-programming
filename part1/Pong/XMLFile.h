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

#include "CommonHeader.h"

// a simple class for loading a XML file
class XML_File
{
private:
	// a list of all the nodes contained in the xml document
	std::vector<tinyxml2::XMLNode*> nodes;
	// the ID for the current node
	unsigned int currentNodeID;
	// a reference to the file
	tinyxml2::XMLDocument file;
public:
	// Constructor & Deconstructor
	XML_File(std::string str, std::string node);
	XML_File(std::string str);
	~XML_File();

	// set the node to read from
	void setNode(std::string nodeName);
	// go up a level to the previous node
	void back();
	// go forward to the next node
	bool next();
	
	// get the value contained inside the node
	std::string getValue(std::string nodeValueID);
};
