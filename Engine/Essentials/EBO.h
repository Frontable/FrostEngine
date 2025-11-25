





#pragma once
#include <glad/glad.h>

class EBO {
public:
    EBO(const unsigned int* data, GLuint size);
    ~EBO();

    void Bind() const;
    void Unbind() const;

private:
    GLuint m_id = 0;
};
