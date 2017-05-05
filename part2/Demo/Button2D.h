
#pragma once

#include "Framework.h"
#include "Texture2D.h"
#include "Text2D.h"

class Button2D
{
    Texture2D * buttonTexture;
    Text2D * buttonText;
    glm::vec4 buttonArea;
public:
    Button2D();
    ~Button2D();

    void setButtonTexture(TextureAsset * texture);
    void setButtonText(FontAsset * font, const char * text);
    void setArea(glm::vec4, Alignment);
    void setArea(glm::vec4);
    bool isPressed(SDL_Event&);

    Texture2D * getTexture();
    Text2D * getText();
};