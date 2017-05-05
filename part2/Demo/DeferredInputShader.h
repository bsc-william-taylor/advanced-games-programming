
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

    void prepare(int VAO, int textureID);
    void prepare(int VAO);
    void compile();

    void run(int geometryType, int start_v, int end_v);
    void run(int start_v, int end_v);
    void run(int vertex_count);
};