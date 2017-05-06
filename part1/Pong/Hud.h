
#pragma once

#include "Framework.h"
#include "Resources.h"

class Display
{
	Label playerScore_1;
	Label playerScore_2;
public:
	Display();
	~Display();

	void render(Renderer&);
	void create(Renderer&);
	void update();
	void enter();

public:
    static int player1;
    static int player2;
};
