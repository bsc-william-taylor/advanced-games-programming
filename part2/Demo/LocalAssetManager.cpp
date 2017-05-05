
#include "LocalAssetManager.h"

LocalAssetManager::LocalAssetManager()
{
    modelFiles.reserve(45);
    textures.reserve(45);
    fonts.reserve(10);
}

LocalAssetManager::~LocalAssetManager()
{
    for (auto& tex : textures)
        delete tex;
    for (auto& model : modelFiles)
        delete model;
    for (auto& font : fonts)
        delete font;
}

TextureAsset * LocalAssetManager::getT(std::string filename)
{
    for (auto& tex : textures)
        if (tex->getName() == filename)
            return tex;
    return NULL;
}

ModelAsset * LocalAssetManager::getM(std::string filename)
{
    for (auto& model : modelFiles)
        if (model->getName() == filename)
            return model;
    return NULL;
}

FontAsset * LocalAssetManager::getL(std::string font, int sz, SDL_Color c)
{
    for (auto& label : fonts)
        if (label->getName() == font) {
            label->openAtSize(sz);
            label->setColour(c);
            return label;
        }
    return nullptr;
}

unsigned int LocalAssetManager::grab(std::initializer_list<std::string> list)
{
    unsigned int start = filenames.size();
    unsigned int loads = NULL;

    filenames.insert(filenames.end(), list.begin(), list.end());

    for (int i = start; i < filenames.size(); i++)
    {
        std::string str = filenames[i].substr(filenames[i].length() - 4);

        if (str == ".jpg" || str == ".png" || str == ".bmp")
        {
            TextureAsset * texture = new TextureAsset(filenames[i].substr(0, filenames[i].length() - 4));
            texture->grabFromFile(filenames[i].c_str());
            textures.push_back(texture);
            ++loads;
        }

        if (str == ".ttf" || str == ".otf")
        {
            FontAsset * font = new FontAsset(filenames[i].substr(0, filenames[i].length() - 4));
            font->grabFromFile(filenames[i].c_str());
            fonts.push_back(font);
            ++loads;
        }

        if (str == ".3DS" || str == ".obj" || str == ".3ds" || str == ".md2" || str == ".md3")
        {
            ModelAsset  * model = new ModelAsset(filenames[i].substr(0, filenames[i].length() - 4));
            model->grabFromFile(filenames[i].c_str());
            modelFiles.push_back(model);
            ++loads;
        }
    }

    return(loads);
}
