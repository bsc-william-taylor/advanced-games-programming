
#pragma once

#include "Framework.h"
#include "GPU.h"

class DeferredInputShader
{
    Program* program;
public:
    DeferredInputShader();
    ~DeferredInputShader();

    Program * getProgram();

    void prepare(int vao, int textureID);
    void prepare(int vao);
    void compile();

    void run(int geometryType, int startVertex, int endVertex);
    void run(int startVertex, int endVertex);
    void run(int vertexVount);
};