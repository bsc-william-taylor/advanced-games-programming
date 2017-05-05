
#pragma once

#include "Framework.h"
#include "GPU.h"

struct PointLight
{
    float area;
    glm::vec3 pointPosition;
    glm::vec3 pointColour;

    float constantA;
    float ambientI;
    float linearA;
    float expA;
};

class DeferredOutputShader
{
    std::vector<PointLight> lights;
    Program* program;
    GLuint UBO;
public:
    DeferredOutputShader();
    ~DeferredOutputShader();

    Program* getProgram();

    void compile();
    void prepare(int ID);
    void run(int start, int end);
    void run(int vertexNum);
};