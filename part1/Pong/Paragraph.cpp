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

#include "Paragraph.h"

Paragraph::Paragraph()
{
	lines.reserve(10);
}

Paragraph::~Paragraph()
{
	for (auto&& line : lines)
	{
		delete(line);
		NULLIFY(line);
	}

	lines.clear();
}

int isNewline(int c)
{
	if(c == '\n') {
		return 1;
	} 
	return 0;
}

void Paragraph::setup(int charlength, std::string filename, std::string node)
{
	XML_File file(filename.c_str(), "file");
	
	std::string data = file.getValue(node.c_str());
	std::string line = "";

	int lengthToRead = charlength;
	int previous = 0;
	int newY = y;

	bool last = false;

	while(true)
	{
		if(previous+lengthToRead >= data.size()) {
			line = data.substr(previous);
			last = true;
		} else{
			line = data.substr(previous, lengthToRead);
		}

		int last_blank = line.find_last_of(" ");
		line = data.substr(previous, last_blank);
		
		Label * label = new Label();
		label->create(font, line, 60);
		label->setPosition(x, newY, align);
		lines.push_back(label);

		previous += last_blank;
		newY += 60;

		if(last)
			break;
	}
}

void Paragraph::setPosition(int x, int y, Alignment a)
{
	this->align = a;
	this->x = x;
	this->y = y;
}

void Paragraph::render(Renderer& renderer)
{
	for(int i = 0; i < lines.size(); i++) {
		if(lines[i] != NULL) {
			renderer.renderLabel(lines[i]);
		}
	}
}
