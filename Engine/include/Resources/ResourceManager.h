#pragma once
#include <string>
#include <unordered_map>

#include "Renderer/Shader.h"

namespace FrostEngine
{
    class ResourceManager
    {
    public:
        static ResourceManager& Instance();

        static bool AddShader(const char* name, Shader&& shader);
        static bool AddShaderFromSource(const char *name, const char *vShader, const char *fShader);
        static bool AddShaderFromFile(const char* name, const char* vShaderPath, const char* fShaderPath);
        static Shader* GetShader(const char* name);
        static void Clear();

    private:
        ResourceManager() = default;
        ~ResourceManager() = default;

        ResourceManager(const ResourceManager&) = delete;
        ResourceManager& operator=(const ResourceManager&) = delete;

        static std::unordered_map<std::string, Shader> m_Shaders;
    };
}