#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

namespace FrostEngine
{
    std::shared_ptr<Texture> TextureLoader::Create(Texture::TextureType _type, const char *_filePath)
    {
        unsigned int id;
        int width, height;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        switch (_type)
        {
        case Texture::TextureType::PIXEL:
            LoadTexture(_filePath, id, width, height, false);
            break;
        case Texture::TextureType::BLENDED:
            LoadTexture(_filePath, id, width, height, true);
            break;
        //add more types as FrameBuffer tex;
        default:
            //assert(false && "the current type is not defined");
            return nullptr;
        }

        return std::make_shared<Texture>(id, width, height, _type ,_filePath);


    }

    bool TextureLoader::LoadTexture(const char *_filePath, unsigned int &_id, int &_width, int &_height, bool blended)
    {
        int channels = 0;

        stbi_set_flip_vertically_on_load(1);
        unsigned char *image = stbi_load(_filePath, &_width, &_height, &channels, 0);

        if (!image)
        {
            std::cout << "Failed to load image: " << _filePath << "\n";
            return false;
        }

        GLenum glFormat = GL_RGBA;
        switch (channels)
        {
        case 1:
            glFormat = GL_RED;
            break;
        case 2:
            glFormat = GL_RG;
            break;
        case 3:
            glFormat = GL_RGB;
            break;
        case 4:
            glFormat = GL_RGBA;
            break;
        default:
            break;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        if (blended)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }

        glTexImage2D(GL_TEXTURE_2D, 0, glFormat, _width, _height, 0, glFormat, GL_UNSIGNED_BYTE, image);
        stbi_image_free(image);

        return true;
    }
}