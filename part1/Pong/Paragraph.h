
#pragma once

#include "Framework.h"
#include "Resources.h"
#include "Renderer.h"
#include "XMLFile.h"
#include "Label.h"

class Paragraph
{
    std::vector<Label *> lines;
    std::string filename;
    Alignment align;
    int x, y;
public:
    Paragraph();
    ~Paragraph();

    void setup(int charlength, std::string filename, std::string node);
    void setPosition(int, int, Alignment);
    void render(Renderer& renderer);
};
