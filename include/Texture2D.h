





#pragma once


class Texture2D
{
    public:
    unsigned int ID;
    Texture2D();
    ~Texture2D();

    unsigned int m_width, m_height, m_nrChannels;
    unsigned int m_internalFormat, m_imageFormat;
    unsigned int m_wrap_s, m_wrap_t;
    unsigned int m_minFilter, m_magFilter;

    void Generate(int width, int height, int nrChannels, int internalFormat, int imageFormat, const unsigned char* data);
    void Use();

};