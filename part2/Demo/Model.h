
#pragma once

#include "Framework.h"
#include "ModelFile.h"
#include "math.h"
#include "GPU.h"

class Model
{
    std::vector<GLuint> tIDs;
    ModelAsset* file;
    Transfer* transfer;
public:
    Model();
    ~Model();

    GLvoid setModel(ModelAsset* model);

    GLuint getTextureIDs(int i);
    GLuint getVertexCount();
    GLuint getMeshCount();
    GLuint getDataID();

    ModelAsset * getModelAsset();
};