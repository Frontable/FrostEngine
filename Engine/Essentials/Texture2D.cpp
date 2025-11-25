






#include "Texture2D.h"
#include <Logger/Logger.h>

Texture2D::Texture2D() {
    glGenTextures(1, &m_id);
    FROST_LOG("Texture created id={%u}", m_id);
}

Texture2D::~Texture2D() {
    if (m_id) {
        glDeleteTextures(1, &m_id);
        FROST_LOG("Texture deleted id={%u}", m_id);
    }
}

Texture2D::Texture2D(Texture2D&& o) noexcept {
    m_id = o.m_id; o.m_id = 0;
    m_width = o.m_width; m_height = o.m_height; m_nrChannels = o.m_nrChannels;
    m_internalFormat = o.m_internalFormat; m_imageFormat = o.m_imageFormat;
}

Texture2D& Texture2D::operator=(Texture2D&& o) noexcept {
    if (this != &o) {
        if (m_id) glDeleteTextures(1, &m_id);
        m_id = o.m_id; o.m_id = 0;
        m_width = o.m_width; m_height = o.m_height; m_nrChannels = o.m_nrChannels;
        m_internalFormat = o.m_internalFormat; m_imageFormat = o.m_imageFormat;
    }
    return *this;
}

void Texture2D::Generate(int width, int height, int nrChannels, GLint internalFormat, GLenum imageFormat, const unsigned char* data) {
    if (!data) {
        FROST_ERROR("Texture generate called with nullptr data ({%d}x{%d})", width, height);
        return;
    }
    m_width = width; m_height = height; m_nrChannels = nrChannels;
    m_internalFormat = internalFormat; m_imageFormat = imageFormat;

    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    FROST_LOG("Texture generated id={%u} size={%d}x{%d} channels={%d}", m_id, m_width, m_height, m_nrChannels);
}

void Texture2D::Bind(GLuint slot) const noexcept {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_id);
}
