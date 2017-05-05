
#pragma once

#include "TextureAsset.h"
#include "GPU.h"

enum class SKYBOX_SIDE 
{
    Right, 
    Front, 
    Back, 
    Left, 
    Top
};

class Skybox
{
    Transfer* cubemapObjectMesh;
    Sampler* cubemapTexture;

    GLfloat distance;

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> uvs;
public:
    Skybox();
    ~Skybox();

    void createSkybox(std::initializer_list<TextureAsset*> assets);
    void setDistance(float distance);

    GLuint getTextureID();
    GLuint getDataID();
};