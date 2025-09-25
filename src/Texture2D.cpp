




#include "Texture2D.h"
#include "glad/glad.h"

Texture2D::Texture2D()
:m_width(0), m_height(0), m_nrChannels(0), m_internalFormat(GL_RGB), m_imageFormat(GL_RGB),m_wrap_s(GL_MIRRORED_REPEAT), m_wrap_t(GL_MIRRORED_REPEAT), 
m_minFilter(GL_LINEAR), m_magFilter(GL_LINEAR)
{
    glGenTextures(1, &ID);
}
Texture2D::~Texture2D()
{

}

void Texture2D::Generate(int width, int height, int nrChannels, int internalFormat, int imageFormat, const unsigned char* data)
{   
    m_width = width;
    m_height = height;
    m_nrChannels = nrChannels;
    m_internalFormat = internalFormat;
    m_imageFormat = imageFormat;

    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_magFilter);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, GL_FALSE, m_imageFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);    
}

void Texture2D::Use()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}