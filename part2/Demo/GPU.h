
#pragma once

#include "Framework.h"
#include "Transfer.h"
#include "Program.h"
#include "Sampler.h"

enum class Geometry
{
    Triangle = 3,
    Cube = 36,
    Quad = 6
};

enum class GraphicsApi
{
    OpenGL,
    DirectX
};

class GPU
{
    const GLubyte* shaderVersion;
    const GLubyte* renderer;
    const GLubyte* version;
    const GLubyte* vendor;

    GLboolean grabbedGPU;
public:
    GPU(GLboolean printDetails = GL_TRUE);
    ~GPU();

    GLboolean has(GraphicsApi api, GLdouble version);
};
