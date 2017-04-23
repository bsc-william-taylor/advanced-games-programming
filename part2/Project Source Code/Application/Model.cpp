
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

#include "Model.h"

// Constructor & Deconstructor
Model::Model()
	: transfer(NULL), file(NULL)
{
}

Model::~Model()
{
}

// returns the number of meshes in the model
GLuint Model::getMeshCount()
{
	return file->getMeshCount();
}

// returns a direct pointer to the model file used to generate the model
ModelAsset * Model::getModelAsset()
{
	return file;
}

void Model::setModel(ModelAsset * assets)
{
	// make sure the pointer is valid
	if (assets != NULL && !transfer) 
	{
		// create the transfer object and pass in the mesh details to it
		transfer = new GPU_Transfer();
		transfer->setTextureCords(assets->getUvs());
		transfer->setVertices(assets->getVertices());
		transfer->setNormals(assets->getNormals());
		// then send the data to the GPU ready for drawing
		transfer->send();

		// then get the list of textures the model uses
		std::vector<TextureAsset*>& textures = assets->getTextures();
		// then loop through and transfer each textures data to the gpu
		for (int i = 0; i < textures.size(); i++) 
		{
			GPU_Sampler * texture = new GPU_Sampler(SINGLE_SAMPLER);

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

			// then store the IDs in our vector so we can use them when drawing
			tIDs.push_back(texture->getID());
		}

		file = assets;	
	}
}

// returns the number of vertices in the model
GLuint Model::getVertexCount()
{
	return file->getVertices().size();
}

// returns the data ID for the models mesh
GLuint Model::getDataID()
{
	return transfer->getID();
}

// returns the texture ID for mesh i
GLuint Model::getTextureIDs(int i)
{
    auto index = file->getMaterialIDs()[i];

	return tIDs[std::min(index, tIDs.size()-1)];
}