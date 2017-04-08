
#include "Screen.h"

// Constructor & Deconstructor
Screen::Screen()
{
	// here we just push back the following screen dimensions
	boxes.push_back({ -200, 0, 200, 1080 }); // LEFT
	boxes.push_back({ 1920, 0, 20, 1080 }); // RIGHT
	boxes.push_back({ 0, 1055, 1920, 250 }); // BOTTOM
	boxes.push_back({ 0, -200, 1920, 225 }); // TOP
}

Screen::~Screen()
{
}

// return a reference to the position vector
std::vector<SDL_Rect>& Screen::getPosition()
{
	return(boxes);
}