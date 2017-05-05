
#include "Model.h"

Model::Model()
    : transfer(nullptr), file(nullptr)
{
}

Model::~Model()
{
}

GLuint Model::getMeshCount()
{
    return file->getMeshCount();
}

ModelAsset * Model::getModelAsset()
{
    return file;
}

void Model::setModel(ModelAsset * assets)
{
    if (assets != nullptr && !transfer)
    {
        transfer = new Transfer();
        transfer->setTextureCords(assets->getUvs());
        transfer->setVertices(assets->getVertices());
        transfer->setNormals(assets->getNormals());
        transfer->send();

        std::vector<TextureAsset*>& textures = assets->getTextures();
        for (int i = 0; i < textures.size(); i++)
        {
            Sampler * texture = new Sampler(SamplerType::SingleSampler);

            TextureAsset * texture_asset = textures[i];
            texture->setTransferQuality(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
            texture->setBitmapWrapping(GL_REPEAT, GL_CLAMP_TO_EDGE);
            texture->setBitmapData(texture_asset->getPixels(),
                texture_asset->getWidth(),
                texture_asset->getHeight(),
                texture_asset->getBPP(),
                texture_asset->getMask()
            );

            texture->send();

            tIDs.push_back(texture->getID());
        }

        file = assets;
    }
}

GLuint Model::getVertexCount()
{
    return file->getVertices().size();
}

GLuint Model::getDataID()
{
    return transfer->getID();
}

GLuint Model::getTextureIDs(int i)
{
    return tIDs[std::min(file->getMaterialIDs()[i], tIDs.size() - 1)];
}