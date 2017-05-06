
#include "Screen.h"

Screen::Screen()
{
    boxes.push_back({ -200, 0, 200, 1080 });
    boxes.push_back({ 1920, 0, 20, 1080 });
    boxes.push_back({ 0, 1055, 1920, 250 });
    boxes.push_back({ 0, -200, 1920, 225 });
}

Screen::~Screen()
{
}

std::vector<SDL_Rect>& Screen::getPosition()
{
    return(boxes);
}