#pragma once
#include <glad/glad.h>

class Texture2D {
public:
    Texture2D();
    ~Texture2D();

    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;
    Texture2D(Texture2D&&) noexcept;
    Texture2D& operator=(Texture2D&&) noexcept;

    void Generate(int width, int height, int nrChannels, GLint internalFormat, GLenum imageFormat, const unsigned char* data);
    void Bind(GLuint slot = 0) const noexcept;

    GLuint ID() const noexcept { return m_id; }
    int Width() const noexcept { return m_width; }
    int Height() const noexcept { return m_height; }

private:
    GLuint m_id{0};
    int m_width{0}, m_height{0}, m_nrChannels{0};
    GLint m_internalFormat{GL_RGB};
    GLenum m_imageFormat{GL_RGB};
};
