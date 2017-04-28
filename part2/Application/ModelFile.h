
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

#pragma once

#include "Framework.h"
#include "TextureAsset.h"
#include "math.h"

using std::vector;
using glm::vec3;

class ModelAsset 
{
private:
	// the vector of all the textures the model uses
	vector<TextureAsset *> textures;
	// the material ID vector for each mesh
	vector<unsigned int> materialID;
	// the number of vertices in each mesh
	vector<unsigned int> meshLength;
	// the vertices for the model
	vector<vec3> vertices;
	// the normals for the model
	vector<vec3> normals;
	// the texture coords for the model
	vector<vec3> uvs;

	// the number of meshes loaded
	unsigned int numberOfMeshes;
public:
	// Constructor & Deconstructor
	ModelAsset(std::string name);
	~ModelAsset();

	// loads the model from the given filename
	void grabFromFile(const char * filename);

	// returns a reference to the textures vector
	vector<TextureAsset *>& getTextures();
	// returns a reference to the materialIDs vector
	vector<unsigned int>& getMaterialIDs();
	// returns a reference to the vertices vector
	vector<vec3>& getVertices();
	// returns a reference to the normals vector
	vector<vec3>& getNormals();
	// returns a reference to the uv cords vector
	vector<vec3>& getUvs();

	// returns the number of vertices in mesh[M_ID]
	unsigned int getMeshLength(int M_ID);
	// returns the number of meshes present in the model
	unsigned int getMeshCount();

	// returns the name of the asset
	std::string getName();
private:
	// a load of private function to help with the setup of meshes, materials and the scene
	bool setupMaterials(const aiScene * scene, const std::string& filename);
	bool setupFromScene(const aiScene * scene, const std::string& filename);
	bool setupMesh(unsigned int ID, const aiMesh * mesh);
private:
	// the name of the asset
	std::string name;
};