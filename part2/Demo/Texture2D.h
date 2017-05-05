
#pragma once

#include "Framework.h"
#include "TextureAsset.h"
#include "math.h"
#include "GPU.h"

class Texture2D
{
    Transfer* transfer;
    Sampler* texture;
public:
    Texture2D();
    ~Texture2D();

    void setTexture(TextureAsset* assets);
    void setArea(glm::vec4 size);

    GLuint getTextureID();
    GLuint getDataID();
};