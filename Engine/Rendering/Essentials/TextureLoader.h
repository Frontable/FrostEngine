#pragma once
#include "Texture.h"
#include <memory>

namespace FrostEngine
{
  
    class TextureLoader
    {
        public:
        TextureLoader() = delete;
        static std::shared_ptr<Texture> Create(Texture::TextureType _type, const char* _filePath); 

        private:
        static bool LoadTexture(const char* _filePath, unsigned int& _id, int& _width, int& _height, bool blended = false);


    };

} 
