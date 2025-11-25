





#include "ResourceManager.h"
#include <Logger/Logger.h>
#include <fstream>
#include <sstream>
#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::map<std::string, Shader> ResourceManager::m_shaders;
std::map<std::string, Texture2D> ResourceManager::m_textures;

std::string ResourceManager::ReadFile(const std::string& path) {
    if (!std::filesystem::exists(path)) {
        FROST_ERROR("File not found: {%s}", path.c_str());
        return {};
    }
    std::ifstream in(path);
    if (!in.is_open()) {
        FROST_ERROR("Failed to open file: {%s}", path.c_str());
        return {};
    }
    std::stringstream ss; ss << in.rdbuf();
    return ss.str();
}

Shader& ResourceManager::LoadShader(const std::string& vPath, const std::string& fPath, const std::string& name) {
    std::string vSrc = ReadFile(vPath);
    std::string fSrc = ReadFile(fPath);
    if (vSrc.empty() || fSrc.empty()) {
        FROST_ERROR("Shader sources empty for '{%s}' ({%s} / {%s})", name.c_str(), vPath.c_str(), fPath.c_str());
        m_shaders.emplace(name, Shader());
        return m_shaders.at(name);
    }
    Shader s; s.Compile(vSrc, fSrc);
    m_shaders.emplace(name, std::move(s));
    FROST_LOG("Loaded shader '{%s}'", name.c_str());
    return m_shaders.at(name);
}

Shader& ResourceManager::GetShader(const std::string& name) {
    auto it = m_shaders.find(name);
    if (it == m_shaders.end()) {
        FROST_ERROR("Requested shader '{%s}' not found", name.c_str());
        throw std::runtime_error("Shader not found: " + name);
    }
    return it->second;
}

Texture2D& ResourceManager::LoadTexture(const std::string& filePath, const std::string& name) {
    if (!std::filesystem::exists(filePath)) {
        FROST_ERROR("Texture file not found: {%s}", filePath.c_str());
        m_textures.emplace(name, Texture2D());
        return m_textures.at(name);
    }
    int w,h,n;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filePath.c_str(), &w, &h, &n, 0);
    if (!data) {
        FROST_ERROR("Failed to load image data: {%s}", filePath.c_str());
        m_textures.emplace(name, Texture2D());
        return m_textures.at(name);
    }

    GLint internal = (n==4) ? GL_RGBA : GL_RGB;
    GLenum imageFmt = (n==4) ? GL_RGBA : GL_RGB;

    Texture2D tex;
    tex.Generate(w, h, n, internal, imageFmt, data);
    m_textures.emplace(name, std::move(tex));
    stbi_image_free(data);
    FROST_LOG("Loaded texture '{%s}' from {%s}", name.c_str(), filePath.c_str());
    return m_textures.at(name);
}

Texture2D& ResourceManager::GetTexture(const std::string& name) {
    auto it = m_textures.find(name);
    if (it == m_textures.end()) {
        FROST_ERROR("Requested texture '{%s}' not found", name.c_str());
        throw std::runtime_error("Texture not found: " + name);
    }
    return it->second;
}

void ResourceManager::Clean() {
    FROST_LOG("Cleaning resources...");
    for (auto& kv : m_shaders) {
        if (kv.second.ID() != 0) glDeleteProgram(kv.second.ID());
    }
    m_shaders.clear();
    m_textures.clear();
}
