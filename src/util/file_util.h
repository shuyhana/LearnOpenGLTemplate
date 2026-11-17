#pragma once

#include <glad/glad.h>
#include <iostream>

enum FileType
{
    FLIETYPE_IMAGE,
    FLIETYPE_SHADER,
    FLIETYPE_MODEL,
    FLIETYPE_FONT
};

const std::string root_path = "/home/hana/workspace/LearnOpenGLTemplate/resource";

extern std::string getFilePath(const std::string& path, FileType fileType);

extern GLuint loadTexture(const char* path, const std::string& directory, bool gamma = false, bool file_vertically = false);
