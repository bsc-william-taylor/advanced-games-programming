
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

#include "ModelFile.h"

// Constructor & Deconstructor
ModelAsset::ModelAsset(std::string name)
{
	this->name = name;
}

ModelAsset::~ModelAsset()
{
	// cleanup all textures loaded
	for (auto& t : textures) 
		SAFE_RELEASE(t);
}

// grabs the model from disk and loads it into memory via ASSIMP
void ModelAsset::grabFromFile(const char * filename)
{
	Assimp::Importer Importer;

	// create a pointer to the loaded structure
	const aiScene * scene = Importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	// if model failed to load
	if (!scene)
	{
		// throw an exception
		throw Error(SYSTEM, std::string("couldnt load model ", filename));
	}
	else
	{
		// else populate vectors with information about the model (vertices, normals etc)
		setupFromScene(scene, filename);
	}
}

// goes through each method and calls the setupMesh and setupMaterials private functions
bool ModelAsset::setupFromScene(const aiScene * scene, const std::string& filename)
{
	// identify the number of meshes
	numberOfMeshes = scene->mNumMeshes;
	for (unsigned int i = 0; i < numberOfMeshes; i++) 
	{
		// then setup each individual mesh (load vertices)
		setupMesh(i, scene->mMeshes[i]);
	}
	
	// then go and load all materials needed
	return setupMaterials(scene, filename);
}

// The following sets up the multiple materials the the mesh will have
bool ModelAsset::setupMaterials(const aiScene* pScene, const std::string& filename)
{	
	// First we identify the filename
	std::string::size_type SlashIndex = filename.find_last_of("/");
	std::string Dir = "";

	// and get the name of the directory so we know where to look for the textures
	if (SlashIndex != 0 && SlashIndex != std::string::npos) 
	{
		Dir = filename.substr(0, SlashIndex+1);
	}

	// The we go through each material
	for (unsigned int i = 0; i < pScene->mNumMaterials; i++) 
	{
		// grab the material
		const aiMaterial* pMaterial = pScene->mMaterials[i];
		// if its a normal texture used for the diffuse colour
		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) 
		{
			// then we get the path for the diffuse texture/textures
			aiString Path;
			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) {
				// Get the correct path to the texture
				std::string FullPath = Dir + Path.data;

				// and load the texture asset
				TextureAsset * textureFile = new TextureAsset(FullPath.substr(0, FullPath.length()-4));
				textureFile->grabFromFile(FullPath.c_str());
				textures.push_back(textureFile);
			}
		}
	}

	// this function shouldn't ever fail
	return true;
}

// sets up each individual mesh and pushes mesh info into the internal vectors
bool ModelAsset::setupMesh(unsigned int , const aiMesh * mesh)
{
	// get the material ID for the mesh & the mesh length
	materialID.push_back(mesh->mMaterialIndex);
	meshLength.push_back(mesh->mNumVertices);

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	// pre allocate memory for the vectors 
	vertices.reserve(mesh->mNumVertices);
	normals.reserve(mesh->mNumVertices);
	uvs.reserve(mesh->mNumVertices);

	// then go through the details of the mesh inserting useful data into to the vectors
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) 
	{
		// here we just get the normals vertices and texture coordinates
		const aiVector3D * u = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;
		const aiVector3D * n = mesh->HasNormals() ? &(mesh->mNormals[i]) : &Zero3D;
		const aiVector3D * v = &(mesh->mVertices[i]);

		// push back the data into the vectors
		vertices.push_back(vec3(v->x, v->y, v->z));
		normals.push_back(vec3(n->x, n->y, n->z));
		uvs.push_back(vec3(u->x, u->y, u->z));
	}

	return true;
}

// returns the vector with all textures via a reference
std::vector<TextureAsset *>& ModelAsset::getTextures()
{
	return textures;
}

// returns the models name
std::string ModelAsset::getName()
{
	return this->name;
}

// returns the number of vertices at mesh (element)
unsigned int ModelAsset::getMeshLength(int element)
{
	return meshLength[element];
}

// returns the number of meshes in the model
unsigned int ModelAsset::getMeshCount()
{
	return numberOfMeshes;
}

// returns the vector with all material IDs
vector<unsigned int>& ModelAsset::getMaterialIDs()
{
	return materialID;
}

// returns the vector with all the vertices for the model
std::vector<glm::vec3>& ModelAsset::getVertices()
{
	return vertices;
}

// returns the vector with all the normals for the model
std::vector<glm::vec3>& ModelAsset::getNormals()
{
	return normals;
}

// returns the vector with all the uvs for the model
std::vector<glm::vec3>& ModelAsset::getUvs()
{
	return this->uvs;
}