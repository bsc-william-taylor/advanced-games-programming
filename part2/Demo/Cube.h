
#pragma once

#include "TextureAsset.h"
#include "Framework.h"
#include "GPU.h"

class Cube
{
    Transfer* transfer;
    Sampler* texture;
public:
    Cube();
    ~Cube();

    void setArea(glm::vec3 position, glm::vec3 size, int repeatCount);
    void setArea(glm::vec3 position, glm::vec3 size);
    void setTexture(TextureAsset* asset);

    GLuint getTextureID();
    GLuint getDataID();
};