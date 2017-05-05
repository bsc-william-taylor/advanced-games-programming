
#pragma once

#include "Framework.h"
#include "LocalAssetManager.h"

class AssetManager
{
    std::vector<LocalAssetManager*> assetManagers;
public:
    AssetManager();
    ~AssetManager();

    LocalAssetManager* grabLocalManager();
};