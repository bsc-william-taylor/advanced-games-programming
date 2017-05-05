
#include "Sampler.h"

GPU_Sampler::GPU_Sampler(SamplerType type)
    : samplerType(type)
{
    min_filter = GL_LINEAR;
    mag_filter = GL_LINEAR;
    hasSent = GL_FALSE;
    wrap_s = GL_REPEAT;
    wrap_t = GL_REPEAT;

    if (samplerType == SamplerType::CubeSampler)
    {
        glGenTextures(1, &cubemapID);
    }
}

GPU_Sampler::~GPU_Sampler()
{
    if (samplerType == SamplerType::SingleSampler)
    {
        glDeleteTextures(1, &bitmaps[0]->bitmapID);
        for (auto& bitmap : bitmaps)
        {
            delete bitmap;
        }
    }
    else
    {
        glDeleteTextures(1, &cubemapID);
        for (auto& bitmap : bitmaps)
        {
            delete bitmap;
        }
    }
}

GLvoid GPU_Sampler::send()
{
    if (!bitmaps.empty())
    {
        if (samplerType == SamplerType::SingleSampler)
        {
            glBindTexture(GL_TEXTURE_2D, bitmaps[0]->bitmapID);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                bitmaps[0]->bitmapWidth,
                bitmaps[0]->bitmapHeight, 0,
                bitmaps[0]->textureFormat,
                GL_UNSIGNED_BYTE,
                bitmaps[0]->data
            );

            if (min_filter == GL_LINEAR_MIPMAP_LINEAR || min_filter == GL_LINEAR_MIPMAP_NEAREST)
            {
                glGenerateMipmap(GL_TEXTURE_2D);
            }
        }

        if (samplerType == SamplerType::CubeSampler)
        {
            GLenum faceType[] =
            {
                GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
                GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                GL_TEXTURE_CUBE_MAP_POSITIVE_Y
            };

            glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            for (int i = 0; i < 6; i++)
            {
                glTexImage2D(faceType[i], 0, GL_RGBA,
                    bitmaps[i]->bitmapWidth,
                    bitmaps[i]->bitmapHeight, 0,
                    bitmaps[i]->textureFormat,
                    GL_UNSIGNED_BYTE,
                    bitmaps[i]->data
                );
            }
        }

        hasSent = GL_TRUE;
    }
}

GLvoid GPU_Sampler::setBitmapWrapping(GLuint s, GLuint t)
{
    wrap_s = s;
    wrap_t = t;
}

GLvoid GPU_Sampler::setTransferQuality(GLuint min, GLuint mag)
{
    min_filter = min;
    mag_filter = mag;
}

GLuint GPU_Sampler::getID()
{
    if (hasSent)
    {
        return samplerType == SamplerType::CubeSampler ? cubemapID : bitmaps[0]->bitmapID;
    }
    else
    {
        return NULL;
    }
}

GLvoid GPU_Sampler::setBitmapData(GLvoid * data, GLuint w, GLuint h, GLuint bpp, GLuint bm)
{
    auto bitmap = new Bitmap();

    if (samplerType == SamplerType::SingleSampler && bitmaps.empty())
    {
        glGenTextures(1, &bitmap->bitmapID);
    }

    bitmap->data = data;
    bitmap->bitmapWidth = w;
    bitmap->bitmapHeight = h;
    bitmap->bytesPerPixel = bpp;
    bitmap->bitmapMask = bm;

    if (bitmap->bytesPerPixel == 4)
    {
        bitmap->textureFormat = bitmap->bitmapMask == 0x000000ff ? GL_RGBA : GL_BGRA;
    }
    else if (bitmap->bytesPerPixel == 3)
    {
        bitmap->textureFormat = bitmap->bitmapMask == 0x000000ff ? GL_RGB : GL_BGR;
    }

    bitmaps.push_back(bitmap);
}