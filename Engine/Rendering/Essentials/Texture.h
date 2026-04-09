#pragma once
#include "glad/glad.h"


namespace FrostEngine
{
    class Texture
    {
        public:
        enum class TextureType { PIXEL = 0, BLENDED, NONE };

        Texture();
        Texture(unsigned _id, int _width, int _height,  TextureType _type = TextureType::PIXEL, const char* _path = "");
        ~Texture() = default;

        const int GetWidth() const { return m_Width; }
        const int GetHeight() const { return m_Height; }

        const unsigned int GetID() const { return m_id; }

        void Bind();
        void Unbind();

        private:
        unsigned int m_id;
        int m_Width, m_Height;
        const char* m_texturePath;
        TextureType m_type;
    };
}