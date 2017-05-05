
#include "Cube.h"

Cube::Cube()
    : transfer(nullptr),
    texture(nullptr)
{
}

Cube::~Cube()
{
    SAFE_RELEASE(transfer);
    SAFE_RELEASE(texture);
}

void Cube::setTexture(TextureAsset * asset)
{
    if (asset != NULL)
    {
        texture = new Sampler(SamplerType::SingleSampler);
        texture->setTransferQuality(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
        texture->setBitmapData(asset->getPixels(),
            asset->getWidth(),
            asset->getHeight(),
            asset->getBPP(),
            asset->getMask()
        );

        texture->send();
    }
}

void Cube::setArea(glm::vec3 position, glm::vec3 size)
{
    setArea(position, size, 1);
}

void Cube::setArea(glm::vec3 position, glm::vec3 size, int r)
{
    if (transfer == NULL)
    {
        glm::vec3 s = position + size;
        glm::vec3 p = position;

        std::vector<glm::vec3> vert = {
            glm::vec3(p[0], p[1], p[2]), glm::vec3(p[0], s[1], p[2]), glm::vec3(s[0], s[1], p[2]),
            glm::vec3(p[0], p[1], p[2]), glm::vec3(s[0], p[1], p[2]), glm::vec3(s[0], s[1], p[2]),
            glm::vec3(p[0], p[1], s[2]), glm::vec3(p[0], s[1], s[2]), glm::vec3(s[0], s[1], s[2]),
            glm::vec3(p[0], p[1], s[2]), glm::vec3(s[0], p[1], s[2]), glm::vec3(s[0], s[1], s[2]),
            glm::vec3(s[0], p[1], p[2]), glm::vec3(s[0], s[1], p[2]), glm::vec3(s[0], s[1], s[2]),
            glm::vec3(s[0], p[1], p[2]), glm::vec3(s[0], p[1], s[2]), glm::vec3(s[0], s[1], s[2]),
            glm::vec3(p[0], p[1], p[2]), glm::vec3(p[0], s[1], p[2]), glm::vec3(p[0], s[1], s[2]),
            glm::vec3(p[0], p[1], p[2]), glm::vec3(p[0], p[1], s[2]), glm::vec3(p[0], s[1], s[2]),
            glm::vec3(p[0], s[1], p[2]), glm::vec3(p[0], s[1], s[2]), glm::vec3(s[0], s[1], s[2]),
            glm::vec3(p[0], s[1], p[2]), glm::vec3(s[0], s[1], p[2]), glm::vec3(s[0], s[1], s[2]),
            glm::vec3(p[0], p[1], p[2]), glm::vec3(p[0], p[1], s[2]), glm::vec3(s[0], p[1], s[2]),
            glm::vec3(p[0], p[1], p[2]), glm::vec3(s[0], p[1], p[2]), glm::vec3(s[0], p[1], s[2]),
        };

        std::vector<glm::vec3> normals = {
            glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0),
            glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0),
            glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0),
            glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0),
            glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0),
            glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0),
            glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0),
            glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0),
            glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0),
            glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0),
            glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0),
            glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 0.0),
        };

        std::vector<glm::vec3> uv_cords = {
            glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0),
            glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0),
            glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0),
            glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0),
            glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0),
            glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0),
            glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0),
            glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0),
            glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0),
            glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0),
            glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0),
            glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0), glm::vec3(0.0*r, 0.0*r, 0.0),
        };

        transfer = new Transfer();
        transfer->setTextureCords(uv_cords);
        transfer->setNormals(normals);
        transfer->setVertices(vert);
        transfer->send();
    }
}

GLuint Cube::getTextureID()
{
    return transfer->getID();
}

GLuint Cube::getDataID()
{
    return texture->getID();
}