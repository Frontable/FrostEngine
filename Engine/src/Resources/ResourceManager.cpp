#include "Resources/ResourceManager.h"
#include "Core/Logger.h"

namespace FrostEngine
{
    std::unordered_map<std::string, Shader> ResourceManager::m_Shaders;

    ResourceManager &ResourceManager::Instance()
    {
        static ResourceManager instance;
        return instance;
    }

    bool ResourceManager::AddShader(const char *name, Shader &&shader)
    {
        auto it = m_Shaders.find(name);
        if (it != m_Shaders.end())
        {
            FROST_WARN("Shader with this name already exists:", name);
            return false;
        }

        m_Shaders.emplace(name, std::move(shader));
        return true;
    }

    bool ResourceManager::AddShaderFromSource(const char *name, const char *vShader, const char *fShader)
    {
        auto it = m_Shaders.find(name);
        if (it != m_Shaders.end())
        {
            FROST_WARN("Shader with this name already exists:", name);
            return false;
        }

        Shader shader;
        if (!shader.CreateFromSource(vShader, fShader))
        {
            FROST_WARN("Failed to create shader from file:", name);
            return false;
        }

        m_Shaders.emplace(name, std::move(shader));
        return true;
    }

    bool ResourceManager::AddShaderFromFile(const char *name, const char *vShaderPath, const char *fShaderPath)
    {
        auto it = m_Shaders.find(name);
        if (it != m_Shaders.end())
        {
            FROST_WARN("Shader with this name already exists:", name);
            return false;
        }

        Shader shader;
        if (!shader.CreateFromFile(vShaderPath, fShaderPath))
        {
            FROST_WARN("Failed to create shader from file:", name);
            return false;
        }

        m_Shaders.emplace(name, std::move(shader));
        return true;
    }

    Shader *ResourceManager::GetShader(const char *name)
    {
        auto it = m_Shaders.find(name);
        if (it != m_Shaders.end())
        {
            return &it->second;
        }

        FROST_WARN("Shader not found:", name);
        return nullptr;
    }

    void ResourceManager::Clear()
    {
        m_Shaders.clear();
    }
}