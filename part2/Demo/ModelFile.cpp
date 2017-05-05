
#include "ModelFile.h"

ModelAsset::ModelAsset(std::string name)
{
    this->name = name;
}

ModelAsset::~ModelAsset()
{
    for (auto& t : textures)
        delete(t);
}

void ModelAsset::grabFromFile(const char * filename)
{
    Assimp::Importer Importer;

    const aiScene * scene = Importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

    if (!scene)
    {
        throw Error(ErrorType::System, std::string("couldnt load model ", filename));
    }
    else
    {
        setupFromScene(scene, filename);
    }
}

bool ModelAsset::setupFromScene(const aiScene * scene, const std::string& filename)
{
    numberOfMeshes = scene->mNumMeshes;
    for (unsigned int i = 0; i < numberOfMeshes; i++)
    {
        setupMesh(i, scene->mMeshes[i]);
    }

    return setupMaterials(scene, filename);
}

bool ModelAsset::setupMaterials(const aiScene* scene, const std::string& filename)
{
    std::string::size_type slashIndex = filename.find_last_of("/");
    std::string directory = "";

    if (slashIndex != 0 && slashIndex != std::string::npos)
    {
        directory = filename.substr(0, slashIndex + 1);
    }

    for (auto i = 0; i < scene->mNumMaterials; i++)
    {
        const aiMaterial* pMaterial = scene->mMaterials[i];
        if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString path;
            if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
            {
                std::string FullPath = directory + path.data;

                TextureAsset * textureFile = new TextureAsset(FullPath.substr(0, FullPath.length() - 4));
                textureFile->grabFromFile(FullPath.c_str());
                textures.push_back(textureFile);
            }
        }
    }

    return true;
}

bool ModelAsset::setupMesh(unsigned int, const aiMesh * mesh)
{
    materialID.push_back(mesh->mMaterialIndex);
    meshLength.push_back(mesh->mNumVertices);

    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

    vertices.reserve(mesh->mNumVertices);
    normals.reserve(mesh->mNumVertices);
    uvs.reserve(mesh->mNumVertices);

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        const aiVector3D * u = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &Zero3D;
        const aiVector3D * n = mesh->HasNormals() ? &(mesh->mNormals[i]) : &Zero3D;
        const aiVector3D * v = &(mesh->mVertices[i]);

        vertices.push_back(vec3(v->x, v->y, v->z));
        normals.push_back(vec3(n->x, n->y, n->z));
        uvs.push_back(vec3(u->x, u->y, u->z));
    }

    return true;
}

std::vector<TextureAsset *>& ModelAsset::getTextures()
{
    return textures;
}

std::string ModelAsset::getName()
{
    return this->name;
}

unsigned int ModelAsset::getMeshLength(int element)
{
    return meshLength[element];
}

unsigned int ModelAsset::getMeshCount()
{
    return numberOfMeshes;
}

vector<unsigned int>& ModelAsset::getMaterialIDs()
{
    return materialID;
}

std::vector<glm::vec3>& ModelAsset::getVertices()
{
    return vertices;
}

std::vector<glm::vec3>& ModelAsset::getNormals()
{
    return normals;
}

std::vector<glm::vec3>& ModelAsset::getUvs()
{
    return this->uvs;
}