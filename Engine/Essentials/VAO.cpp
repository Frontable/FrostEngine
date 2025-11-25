




#include "VAO.h"
#include <Logger/Logger.h>

VAO::VAO() {
    glGenVertexArrays(1, &m_id);
    FROST_LOG("VAO created (id={})", m_id);
}

VAO::~VAO() {
    if (m_id) {
        glDeleteVertexArrays(1, &m_id);
        FROST_LOG("VAO deleted (id={})", m_id);
    }
}

void VAO::Bind() const {
    glBindVertexArray(m_id);
}

void VAO::Unbind() const {
    glBindVertexArray(0);
}

void VAO::ApplyLayout(const Layout& layout) {
    Bind();
    GLuint offset = 0;
    for (GLuint i = 0; i < layout.Elements().size(); i++) {
        const auto& e = layout.Elements()[i];

        glEnableVertexAttribArray(i);
        glVertexAttribPointer(
            i,
            e.count,
            e.type,
            e.normalized,
            layout.Stride(),
            (void*)(uintptr_t)offset
        );

        offset += e.size;
    }
}
