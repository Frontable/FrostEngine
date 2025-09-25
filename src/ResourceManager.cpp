






#include "ResourceManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION


std::map<std::string, Shader> ResourceManager::shaders;
std::map<std::string, Texture2D> ResourceManager::textures;

Shader& ResourceManager::GetShader(const std::string& name)
{
    return shaders[name];
}

Shader& ResourceManager::LoadShader(const char* vShaderPath, const char* fShaderPath, const std::string& name)
{

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    vShaderFile.open(vShaderPath);
    fShaderFile.open(fShaderPath);
    if (!vShaderFile.is_open()) {
        std::cerr << "Error opening file: " << vShaderPath << std::endl;        
    }
    if (!fShaderFile.is_open()) {
        std::cerr << "Error opening file: " << vShaderPath << std::endl;        
    }

    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    std::string vShaderString, fShaderString;
    vShaderString = vShaderStream.str();
    fShaderString = fShaderStream.str();

    const char* vShaderCode;
    const char* fShaderCode;

    vShaderCode = vShaderString.c_str();
    fShaderCode = fShaderString.c_str();
    
    
    shaders[name].Compile(vShaderCode, fShaderCode);

    return shaders[name];

}

Texture2D& ResourceManager::GetTexture(const std::string& name)
{
    return textures[name];
}

void ResourceManager::LoadTexture(const char* filePath, const std::string& name)
{
    stbi_set_flip_vertically_on_load(1);
    int width, height, nrChannels;
    unsigned int internalFormat, imageFormat;
    unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, NULL);
    if(!data)
    {
        std::cout<<"Failed to load Texture!"<<std::endl;
    }

    if(nrChannels == 1)
    {
        internalFormat = GL_RED;
        imageFormat = GL_RED;
    }else if(nrChannels == 2)
    {
        internalFormat = GL_RG;
        imageFormat = GL_RG;
    }else if(nrChannels == 3)
    {
        internalFormat = GL_RGB;
        imageFormat = GL_RGB;
    }else if(nrChannels == 4)
    {
        internalFormat = GL_RGBA;
        imageFormat = GL_RGBA;
    }else
    {
        internalFormat = GL_RGB;
        imageFormat = GL_RGB;
    }
    std::cout<<"Loaded texture: " << filePath << "\n with width: " << width << " height: " << height << " and channels: " << nrChannels << std::endl;
    textures[name].Generate(width, height, nrChannels, internalFormat, imageFormat, data);  
    
    stbi_image_free(data);

}


void ResourceManager::Clean()
{

    for(auto& s : shaders)
    {
        glDeleteProgram(s.second.ID);
    }

    for(auto& t : textures)
    {
        glDeleteTextures(1, &t.second.ID);
    }

}