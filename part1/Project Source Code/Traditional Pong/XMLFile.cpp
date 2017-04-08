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

#include "XMLFile.h"
#include "Exception.h"

// Constructor & Deconstructor
XML_File::XML_File(std::string str)
	: currentNodeID(-1)
{
	// load the file
	file.LoadFile(str.c_str());
}

XML_File::XML_File(std::string str, std::string node)
	: currentNodeID(-1)
{
	// load the file
	file.LoadFile(str.c_str());

	// then set the initial node
	setNode(node);
}

XML_File::~XML_File()
{	
}

// sets the node to read from
void XML_File::setNode(std::string str)
{
	// the found node as a pointer
	tinyxml2::XMLNode * node;

	// if we are at the start of the file
	if(currentNodeID == -1)
	{
		// find the first child element from the files first node
		node = file.FirstChildElement(str.c_str());
	}
	else
	{
		// else 
		node = nodes[currentNodeID]->FirstChildElement(str.c_str());
	}

	// if we found the node
	if(node != NULL)
	{
		// increment the node counter
		++currentNodeID;

		// and push the new node into the list
		nodes.push_back(node);
	}
	else
	{
		// on fail throw an exception
		throw Error(FILE_IO, "couldnt find node " + str, WILLIAM);
	}
}

// returns the value at the currently loaded node
std::string XML_File::getValue(std::string str)
{
	// the value to be returned to the user
	std::string data = "";

	try
	{
		tinyxml2::XMLElement * node = nodes[currentNodeID]->FirstChildElement(str.c_str());

		// if node cannot be found throw an exception
		if(node == NULL)
		{
			throw Error(FILE_IO, "couldnt retrieve xml node", WILLIAM);
		}
		else
		{
			// else retrieve the value
			data = node->GetText();
		}
	}
	catch(...)
	{
		// if an exception is thrown throw another one
		throw Error(FILE_IO, "couldnt grab xml node", WILLIAM);
	}

	// return value contained at node to the user
	return data;
}

// pops one of the nodes and points to the previous node
void XML_File::back()
{
	// pop the last node inserted
	nodes.pop_back();
	currentNodeID--;
}

// goes to the next sibling or next node
bool XML_File::next()
{
	// try and grab the next node
	tinyxml2::XMLNode * next = nodes[currentNodeID]->NextSibling();

	// if it was not found
	if(next == NULL)
	{
		// throw an exception
		throw Error(FILE_IO, "Couldnt grab next xml node", WILLIAM);

		// and return false to indicate failure
		return false;
	}
	else
	{
		// on success set the current node to the next node
		nodes[currentNodeID] = next;

		// return true to indicate success
		return true;
	}
}
