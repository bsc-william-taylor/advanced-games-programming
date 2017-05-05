
#pragma once

#include "Framework.h"

enum class SamplerType
{
    SingleSampler,
    CubeSampler
};

struct Bitmap
{
    GLenum textureFormat;
    GLuint bitmapHeight;
    GLuint bitmapMask;
    GLuint bytesPerPixel;
    GLuint bitmapWidth;
    GLuint bitmapID;
    GLvoid* data;
};

class Sampler
{
    std::vector<Bitmap*>  bitmaps;
    SamplerType samplerType;

    GLuint cubemapID;
    GLuint min_filter;
    GLuint mag_filter;
    GLuint wrap_s;
    GLuint wrap_t;

    GLboolean hasSent;
public:
    Sampler(SamplerType type);
    ~Sampler();

    GLvoid setBitmapData(GLvoid*, GLuint, GLuint, GLuint, GLuint);
    GLvoid setBitmapWrapping(GLuint s, GLuint t);
    GLvoid setTransferQuality(GLuint, GLuint);
    GLvoid send();
    GLuint getID();
};