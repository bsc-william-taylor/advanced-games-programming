
#pragma once

#include "Framework.h"
#include "GPU.h"

class OrthoShader
{
	Program* program;
public:
	OrthoShader();
	~OrthoShader();

	Program* getProgram();

	void prepare(int vao, int textureID);
	void compile();
	void run(int num);
};