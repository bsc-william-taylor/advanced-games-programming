
#pragma once

#include "Framework.h"
#include "GPU.h"

enum class GeometryBufferElement 
{
    Position,
    Diffuse,
    Normal,
};

class GeometryBuffer
{
    GLuint finalTexture;
    GLuint bufferHeight;
    GLuint bufferWidth;
    GLuint depthTexture;
    GLuint framebuffer;
    GLuint positionTexture;
    GLuint diffuseTexture;
    GLuint normalTexture;
public:
    GeometryBuffer();
    ~GeometryBuffer();

    glm::vec2 getBufferSize();

    GLvoid setupGeometryBuffer(int w, int h);
    GLvoid prepareForReading();
    GLvoid prepareForWriting();
    GLvoid startFrame();
    GLvoid stopFrame();
};