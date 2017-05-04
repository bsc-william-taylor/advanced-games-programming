
/**
*
* Copyright (c) 2014 : William Taylor : wi11berto@yahoo.co.uk
*
* This software is provided 'as-is', without any
* express or implied warranty. In no event will
* the authors be held liable for any damages
* arising from the use of this software.
*
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute
* it freely, subject to the following restrictions:
*
* 1. The origin of this software must not be misrepresented;
*    you must not claim that you wrote the original software.
*    If you use this software in a product, an acknowledgment
*    in the product documentation would be appreciated but
*    is not required.
*
* 2. Altered source versions must be plainly marked as such,
*    and must not be misrepresented as being the original software.
*
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef __ASSET_MANAGER_H__
#define __ASSET_MANAGER_H__

#include "Framework.h"
#include "LocalAssetManager.h"

// This is a simple class that just returns a local asset manager to a scene
class AssetManager
{
private:
	// the vector of state local asset managers
	std::vector<LocalAssetManager*> stateAssetManagers;
public:
	// Constructor & Deconstructor
	AssetManager();
	~AssetManager();

	// returns new instance to a local asset manager for the scene to use
	LocalAssetManager * grabLocalManager();
};

#endif