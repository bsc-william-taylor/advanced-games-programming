
#pragma once

#include "Framework.h"
#include "TextureAsset.h"
#include "FontAsset.h"
#include "ModelFile.h"

class LocalAssetManager
{
    std::vector<std::string> filenames;
    std::vector<TextureAsset*> textures;
    std::vector<ModelAsset*> modelFiles;
    std::vector<FontAsset*> fonts;
public:
    LocalAssetManager();
    ~LocalAssetManager();

    unsigned int grab(std::initializer_list<std::string>);

    TextureAsset * getT(std::string filename);
    ModelAsset * getM(std::string filename);
    FontAsset * getL(std::string font, int, SDL_Color);
};