

#include "Transfer.h"

GPU_Transfer::GPU_Transfer()
    : indices(NULL),
    hasSent(GL_FALSE)
{
    glGenVertexArrays(1, &vertexArrayObject);
    for (int i = 0; i < (int)BufferIDs::Size; i++)
    {
        objectData[i] = NULL;
        objectIDs[i] = NULL;
    }
}

GPU_Transfer::~GPU_Transfer()
{
    glDeleteVertexArrays(1, &vertexArrayObject);
    for (int i = 0; i < (int)BufferIDs::Size; i++)
        objectIDs[i] ? glDeleteBuffers(1, &objectIDs[i]) : NULL;
}

GLuint GPU_Transfer::getID()
{
    if (hasSent)
    {
        return vertexArrayObject;
    }
    else
    {
        return NULL;
    }
}

GLuint GPU_Transfer::getIndexID()
{
    return objectIDs[(int)BufferIDs::IndicesID];
}

void GPU_Transfer::send()
{
    glBindVertexArray(vertexArrayObject);

    if (objectData[(int)BufferIDs::VertexID] != NULL)
    {
        glGenBuffers(1, &objectIDs[(int)BufferIDs::VertexID]);
        glBindBuffer(GL_ARRAY_BUFFER, objectIDs[(int)BufferIDs::VertexID]);
        glBufferData(GL_ARRAY_BUFFER,
            (*objectData[(int)BufferIDs::VertexID]).size() * (sizeof(GLfloat) * 3),
            (*objectData[(int)BufferIDs::VertexID]).data(),
            GL_STATIC_DRAW
        );

        glEnableVertexAttribArray((int)BufferIDs::VertexID);
        glVertexAttribPointer((int)BufferIDs::VertexID, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if (objectData[(int)BufferIDs::NormalID] != NULL)
    {
        glGenBuffers(1, &objectIDs[(int)BufferIDs::NormalID]);
        glBindBuffer(GL_ARRAY_BUFFER, objectIDs[(int)BufferIDs::NormalID]);
        glBufferData(GL_ARRAY_BUFFER,
            (*objectData[(int)BufferIDs::NormalID]).size() * (sizeof(GLfloat) * 3),
            (*objectData[(int)BufferIDs::NormalID]).data(),
            GL_STATIC_DRAW
        );

        glEnableVertexAttribArray((int)BufferIDs::NormalID);
        glVertexAttribPointer((int)BufferIDs::NormalID, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if (objectData[(int)BufferIDs::TextureID] != NULL)
    {
        glGenBuffers(1, &objectIDs[(int)BufferIDs::TextureID]);
        glBindBuffer(GL_ARRAY_BUFFER, objectIDs[(int)BufferIDs::TextureID]);
        glBufferData(GL_ARRAY_BUFFER,
            (*objectData[(int)BufferIDs::TextureID]).size() * (sizeof(GLfloat) * 3),
            (*objectData[(int)BufferIDs::TextureID]).data(),
            GL_STATIC_DRAW
        );

        glEnableVertexAttribArray((int)BufferIDs::TextureID);
        glVertexAttribPointer((int)BufferIDs::TextureID, 3, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if (objectData[(int)BufferIDs::ColourID] != NULL)
    {
        glGenBuffers(1, &objectIDs[(int)BufferIDs::ColourID]);
        glBindBuffer(GL_ARRAY_BUFFER, objectIDs[(int)BufferIDs::ColourID]);
        glBufferData(GL_ARRAY_BUFFER,
            (*objectData[(int)BufferIDs::ColourID]).size() * (sizeof(GLfloat) * 3),
            (*objectData[(int)BufferIDs::ColourID]).data(),
            GL_STATIC_DRAW
        );

        glEnableVertexAttribArray((int)BufferIDs::ColourID);
        glVertexAttribPointer((int)BufferIDs::ColourID, 4, GL_FLOAT, GL_FALSE, 0, 0);
    }

    if (indices != NULL)
    {
        glGenBuffers(1, &objectIDs[(int)BufferIDs::IndicesID]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objectIDs[(int)BufferIDs::IndicesID]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
            (*indices).size() * sizeof(GLuint),
            &(*indices)[0],
            GL_STATIC_DRAW
        );
    }

    glBindVertexArray(NULL);
    hasSent = GL_TRUE;
}

void GPU_Transfer::setVerticesColour(std::vector<glm::vec3>& data)
{
    objectData[(int)BufferIDs::ColourID] = &data;
}

void GPU_Transfer::setTextureCords(std::vector<glm::vec3>& data)
{
    objectData[(int)BufferIDs::TextureID] = &data;
}

void GPU_Transfer::setVertices(std::vector<glm::vec3>& data)
{
    objectData[(int)BufferIDs::VertexID] = &data;
}

GLvoid GPU_Transfer::setIndices(std::vector<GLuint>& data)
{
    indices = &data;
}

void GPU_Transfer::setNormals(std::vector<glm::vec3>& data)
{
    objectData[(int)BufferIDs::NormalID] = &data;
}