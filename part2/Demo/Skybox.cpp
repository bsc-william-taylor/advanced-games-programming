

#include "Skybox.h"

Skybox::Skybox()
    : cubemapObjectMesh(nullptr),
    cubemapTexture(nullptr),
    distance(-1)
{
}

Skybox::~Skybox()
{
    SAFE_RELEASE(cubemapObjectMesh);
    SAFE_RELEASE(cubemapTexture);
}

void Skybox::createSkybox(std::initializer_list<TextureAsset*> assets)
{
    if (assets.size() == 6 && distance != -1)
    {
        cubemapTexture = new Sampler(SamplerType::CubeSampler);

        for (auto& texture : assets)
        {
            if (texture != NULL)
            {
                cubemapTexture->setBitmapData(texture->getPixels(),
                    texture->getWidth(),
                    texture->getHeight(),
                    texture->getBPP(),
                    texture->getMask()
                );
            }
        }

        cubemapTexture->send();
        cubemapObjectMesh = new Transfer();
        cubemapObjectMesh->setVertices(vertices);
        cubemapObjectMesh->setNormals(normals);
        cubemapObjectMesh->send();
    }
}

void Skybox::setDistance(float distance)
{
    this->distance = distance;

    vertices = {
        glm::vec3(-distance, -distance, -distance), glm::vec3(distance, -distance, -distance), glm::vec3(distance, distance, -distance),
        glm::vec3(-distance, -distance, -distance), glm::vec3(-distance, distance, -distance), glm::vec3(distance, distance, -distance),
        glm::vec3(distance, -distance, -distance), glm::vec3(distance, distance, -distance), glm::vec3(distance, distance, distance),
        glm::vec3(distance, -distance, -distance), glm::vec3(distance, distance, distance), glm::vec3(distance, -distance, distance),
        glm::vec3(-distance, -distance, distance), glm::vec3(distance, -distance, distance), glm::vec3(distance, distance, distance),
        glm::vec3(-distance, -distance, distance), glm::vec3(-distance, distance, distance), glm::vec3(distance, distance, distance),
        glm::vec3(-distance, -distance, -distance), glm::vec3(-distance, distance, -distance), glm::vec3(-distance, distance, distance),
        glm::vec3(-distance, -distance, -distance), glm::vec3(-distance, distance, distance), glm::vec3(-distance, -distance, distance),
        glm::vec3(-distance, distance, -distance), glm::vec3(-distance, distance, distance), glm::vec3(distance, distance, distance),
        glm::vec3(-distance, distance, -distance), glm::vec3(distance, distance, distance), glm::vec3(distance, distance, -distance),
        glm::vec3(-distance, -distance, -distance), glm::vec3(-distance, -distance, distance), glm::vec3(distance, -distance, distance),
        glm::vec3(-distance, -distance, -distance), glm::vec3(distance, -distance, distance), glm::vec3(distance, -distance, -distance)
    };

    for (auto& v : vertices)
    {
        normals.push_back(glm::vec3(0.0, 0.0, 0.0));
    }
}

GLuint Skybox::getTextureID()
{
    return cubemapTexture->getID();
}

GLuint Skybox::getDataID()
{
    return cubemapObjectMesh->getID();
}