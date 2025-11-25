




#include "VBO.h"
#include <Logger/Logger.h>

VBO::VBO(const void* data, GLuint size) {
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    FROST_LOG("VBO created (id={})", m_id);
}

VBO::~VBO() {
    if (m_id) {
        glDeleteBuffers(1, &m_id);
        FROST_LOG("VBO deleted (id={})", m_id);
    }
}

void VBO::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VBO::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
