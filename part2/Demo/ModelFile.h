
#pragma once

#include "Framework.h"
#include "TextureAsset.h"
#include "math.h"

using std::vector;
using glm::vec3;

class ModelAsset
{
    vector<TextureAsset*> textures;
    vector<unsigned int> materialID;
    vector<unsigned int> meshLength;
    vector<vec3> vertices;
    vector<vec3> normals;
    vector<vec3> uvs;

    unsigned int numberOfMeshes;
    std::string name;
public:
    ModelAsset(std::string name);
    ~ModelAsset();

    void grabFromFile(const char* filename);

    vector<TextureAsset*>& getTextures();
    vector<unsigned int>& getMaterialIDs();
    vector<vec3>& getVertices();
    vector<vec3>& getNormals();
    vector<vec3>& getUvs();

    unsigned int getMeshLength(int M_ID);
    unsigned int getMeshCount();

    std::string getName();
private:
    bool setupMaterials(const aiScene* scene, const std::string& filename);
    bool setupFromScene(const aiScene* scene, const std::string& filename);
    bool setupMesh(unsigned int ID, const aiMesh * mesh);
};