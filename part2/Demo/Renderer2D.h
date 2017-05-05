
#pragma once

#include "OrthoShader.h"
#include "Text2D.h"
#include "Texture2D.h"
#include "Button2D.h"

class Renderer2D
{
    OrthoShader shader;
public:
    Renderer2D();
    ~Renderer2D();

    void setMatrixForObject(const char* matrix, glm::mat4& value);
    void renderTexture(Texture2D* texture2D);
    void renderButton(Button2D* button2D);
    void renderLabel(Text2D* text2D);
    void createRenderer();
    void prepare();
    void present();
};