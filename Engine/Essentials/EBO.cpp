#include "EBO.h"
#include <Logger/Logger.h>

EBO::EBO(const unsigned int* data, GLuint size) {
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    FROST_LOG("EBO created (id={})", m_id);
}

EBO::~EBO() {
    if (m_id) {
        glDeleteBuffers(1, &m_id);
        FROST_LOG("EBO deleted (id={})", m_id);
    }
}

void EBO::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void EBO::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
