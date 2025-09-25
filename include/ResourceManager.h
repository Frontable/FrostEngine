





#pragma once

#include <map>
#include <string>
#include "Shader.h"
#include "Texture2D.h"


class ResourceManager
{
    public:
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture2D> textures;

    static Shader& GetShader(const std::string& name);
    static Shader& LoadShader(const char* vShaderPath, const char* fShaderPath, const std::string& name);

    static Texture2D& GetTexture(const std::string& name);
    static void LoadTexture(const char* filePath, const std::string& name);
    
    
};