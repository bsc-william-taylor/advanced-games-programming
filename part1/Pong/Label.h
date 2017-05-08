
#pragma once

#include "MajorInclude.h"

enum class Alignment 
{
	CENTER, LEFT, RIGHT
};

struct FontEntry 
{
	std::string filename;
	TTF_Font * font;
	unsigned sz;
};

class Label
{
	SDL_Surface* surface;
	SDL_Color colour;
	SDL_Rect position;

	const char* text;

    static std::vector<FontEntry *> fonts;
    static unsigned int reference_count;
public:
	Label();
	~Label();

    TTF_Font* checkForDuplicates(std::string str, unsigned);

	void setPosition(int x, int y, Alignment);
	void create(std::string, std::string, int);
	void setColour(SDL_Color colour);

	const char* getText();

	SDL_Surface * get();
	SDL_Rect& getPosition();

	double getAngle();
};
