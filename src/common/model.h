#pragma once

#include <glad/glad.h>

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"

class Model
{
public:
    std::vector<Texture>    texture_loaded;
    std::vector<Mesh>       meshes;
    std::string             directory;
    bool                    gammaCorrection;

    Model(const std::string& path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);
    }

    void Draw(Shader& shader)
    {
        for (size_t i = 0; i < meshes.size(); ++i)
        {
            meshes[i].Draw(shader);
        }
    }

private:
    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

