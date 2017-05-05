
#pragma once

#include "Framework.h"
#include "ModelFile.h"
#include "math.h"
#include "GPU.h"

struct HeightmapSurface
{
    std::vector<glm::vec3> vertices;
    glm::vec3 normal;
};

enum class Side 
{
    Top, 
    TopRight, 
    Right, 
    BottomRight,
    Bottom, 
    BottomLeft, 
    Left, 
    TopLeft
};

class Heightmap
{
    std::vector<std::vector<HeightmapSurface *>> faces;
    std::vector<std::vector<float>> terrain_heights;
    std::vector<glm::vec3> vn;

    Sampler* texture;
    GLuint vertexCount;
    Transfer* mesh;

    glm::vec2 size;
public:
    Heightmap();
    ~Heightmap();

    glm::vec2 getHeightmapSize();
    glm::vec3 getSurfaceNormal(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);

    GLvoid averageNormals(std::vector<glm::vec3>& vertices);
    GLvoid create(TextureAsset * file, std::string, float _x, float _y);

    GLuint getVertexCount();
    GLuint getVertexID();
    GLuint getTexture();

    GLfloat getY(FIBITMAP * sprite, int x, int y, float scale_y);
    GLfloat getHeightAt(int x, int y);

    HeightmapSurface * getFace(Side side, GLuint x, GLuint b, GLuint size);
};
