
#pragma once

#include "Framework.h"
#include "Resources.h"

class Display
{
    Label playerScoreOne;
    Label playerScoreTwo;
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
