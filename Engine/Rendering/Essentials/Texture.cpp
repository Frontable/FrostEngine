#include "Texture.h"

namespace FrostEngine
{
    Texture::Texture()
    :Texture(0, 0, 0, TextureType::NONE)
    {
    }
    //Texture(unsigned _id, int _width, int _height,  TextureType _type = TextureType::PIXEL, const char* _path = "");
    Texture::Texture(unsigned _id, int _width, int _height, TextureType _type, const char* _path)
    :m_id(_id), m_Width(_width), m_Height(_height), m_type(_type), m_texturePath(_path)
    {
    }

    void Texture::Bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
    }
    void Texture::Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}