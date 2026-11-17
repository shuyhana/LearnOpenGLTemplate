#include "file_util.h"

#define STB_IMAGE_IMPLEMENTATION
#include "includes/stb_image.h"

std::string getFilePath(const std::string &path, FileType fileType)
{
    switch (fileType)
    {
    case FileType::FLIETYPE_IMAGE:
        return root_path + "/images/" + path;
    case FileType::FLIETYPE_SHADER:
        return root_path + "/shaders/" + path;
    case FileType::FLIETYPE_MODEL:
        return root_path + "/models/" + path;
    case FileType::FLIETYPE_FONT:
        return root_path + "/fonts/" + path;
    default:
        break;
    }

    return "";
}

GLuint loadTexture(const char *path, const std::string &directory, bool gamma, bool file_vertically)
{
    GLuint textureID;
    glGenTextures(1, &textureID);

    std::string filename = std::string(path);
    if (!directory.empty())
        filename = directory + '/' + filename;
    else
        filename = getFilePath(filename, FileType::FLIETYPE_IMAGE);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(file_vertically);
    GLubyte* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format {};
        switch (nrComponents)
        {
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            break;
        }

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
