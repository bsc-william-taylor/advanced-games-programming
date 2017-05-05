
#include "AssetManager.h"

AssetManager::AssetManager()
{
    assetManagers.reserve(10);
}

AssetManager::~AssetManager()
{
    assetManagers.clear();
}

LocalAssetManager * AssetManager::grabLocalManager()
{
    assetManagers.push_back(new LocalAssetManager());
    return assetManagers.back();
}