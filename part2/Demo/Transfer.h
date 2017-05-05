
#pragma once

#include "Framework.h"
#include "math.h"

enum class BufferIDs
{
    VertexID,
    NormalID,
    TextureID,
    ColourID,
    IndicesID,
    Size
};

class GPU_Transfer
{
    GLuint vertexArrayObject;
    GLuint objectIDs[(int)BufferIDs::Size];
    GLboolean hasSent;

    std::vector<glm::vec3>* objectData[(int)BufferIDs::Size];
    std::vector<GLuint>* indices;
public:
    GPU_Transfer();
    ~GPU_Transfer();

    GLvoid setVerticesColour(std::vector<glm::vec3>& colour);
    GLvoid setTextureCords(std::vector<glm::vec3>& coords);
    GLvoid setVertices(std::vector<glm::vec3>& vertices);
    GLvoid setNormals(std::vector<glm::vec3>& normals);
    GLvoid setIndices(std::vector<GLuint>& indices);
    GLvoid send();

    GLuint getIndexID();
    GLuint getID();
};
