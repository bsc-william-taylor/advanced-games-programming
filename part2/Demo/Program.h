
#pragma once

#include "Framework.h"

#ifndef SHADER_VERSION
    #define SHADER_VERSION "#version 330 \n" 
#else
    #error SHADER_VERSION : multiple definition
#endif

#ifndef SRC
    #define SRC(str) SHADER_VERSION #str
#else
    #error SRC : multiple definition
#endif

class Program
{
    GLboolean compiled;
    GLuint fragmentID;
    GLuint programID;
    GLuint vertexID;
public:
    Program();
    ~Program();

    GLvoid setFragmentSource(const char* source);
    GLvoid setVertexSource(const char* source);
    GLvoid setMatrix(GLchar* nm, float* m);
    GLvoid setVector(GLchar* name, glm::vec2 vec);
    GLvoid setInteger(GLchar* name, int v);
    GLvoid prepare(GLuint VAO);
    GLvoid bind(GLuint t_ID);
    GLvoid unbindShader();
    GLvoid bindShader();
    GLuint getID();

    GLvoid run(GLuint shapeType, GLuint startingVertex, GLuint vertexCount);
    GLvoid run(GLuint startingVertex, GLuint vertexCount);
    GLvoid run(GLuint vertexCount);

    GLboolean compile();
};