
#pragma once

#include "Framework.h"
#include "FontAsset.h"
#include "math.h"
#include "GPU.h"

enum class Alignment
{
    Center,
    Right,
    Left
};

class Text2D
{
    Transfer* transfer;
    Sampler* texture;

    GLuint height;
    GLuint width;
public:
    Text2D();
    ~Text2D();

    void setFont(FontAsset* text_font, const char* text);
    void setArea(glm::vec2 size, Alignment textAlignment);
    void setArea(glm::vec2 size);

    GLuint getTextureID();
    GLuint getDataID();
};
