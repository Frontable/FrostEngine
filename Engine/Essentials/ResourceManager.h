




#pragma once
#include <map>
#include <string>
#include "Shader.h"
#include "Texture2D.h"

class ResourceManager {
public:
    static Shader& LoadShader(const std::string& vertexPath, const std::string& fragPath, const std::string& name);
    static Shader& GetShader(const std::string& name);

    static Texture2D& LoadTexture(const std::string& filePath, const std::string& name);
    static Texture2D& GetTexture(const std::string& name);

    static void Clean();

private:
    static std::map<std::string, Shader> m_shaders;
    static std::map<std::string, Texture2D> m_textures;
    static std::string ReadFile(const std::string& path);
};
