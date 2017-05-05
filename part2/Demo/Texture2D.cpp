
#include "Texture2D.h"

Texture2D::Texture2D()
    : transfer(nullptr),
    texture(nullptr)
{
}

Texture2D::~Texture2D()
{
    SAFE_RELEASE(transfer);
    SAFE_RELEASE(texture);
}

void Texture2D::setTexture(TextureAsset * asset)
{
    if (asset != nullptr)
    {
        texture = new Sampler(SamplerType::SingleSampler);
        texture->setBitmapData(asset->getPixels(),
            asset->getWidth(),
            asset->getHeight(),
            asset->getBPP(),
            asset->getMask()
        );

        texture->send();
    }
}

void Texture2D::setArea(glm::vec4 size)
{
    std::vector<glm::vec3> vert = {
        glm::vec3(size[0], size[1] + size[3], 0.1), 
        glm::vec3(size[0] + size[2], size[1] + size[3], 0.1), 
        glm::vec3(size[0] + size[2], size[1], 0.1),
        glm::vec3(size[0], size[1] + size[3], 0.1), 
        glm::vec3(size[0], size[1], 0.1), 
        glm::vec3(size[0] + size[2], size[1], 0.1),
    };

    std::vector<glm::vec3> uvs = {
        glm::vec3(0.0, 0.0, 0.0), glm::vec3(1.0, 0.0, 0.0), glm::vec3(1.0, 1.0, 0.0),
        glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0), glm::vec3(1.0, 1.0, 0.0),
    };

    transfer = new Transfer();
    transfer->setTextureCords(uvs);
    transfer->setVertices(vert);
    transfer->send();
}

GLuint Texture2D::getTextureID()
{
    return texture->getID();
}

GLuint Texture2D::getDataID()
{
    return transfer->getID();
}