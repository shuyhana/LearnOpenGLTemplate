#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>

#include "shader.h"

#define MAX_BONE_INFLUENCE 4

typedef struct Vectex_t
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoord;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
    // bone indexes which will influence this vertex
    GLint m_BoneIDs[MAX_BONE_INFLUENCE];
    // weights from each bone
    GLfloat m_Weights[MAX_BONE_INFLUENCE];
} Vertex;

typedef struct Texture_t
{
    GLuint id;
    std::string type;
    std::string path;
} Texture;

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices,
         std::vector<GLuint> indices,
         std::vector<Texture> textures);
    ~Mesh() = default;

    void Draw(Shader& shader);

public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    GLuint VAO;

private:
    void setupMesh();

private:
    GLuint VBO, EBO;
};

