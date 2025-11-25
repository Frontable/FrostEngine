




#pragma once
#include <glad/glad.h>
#include <vector>

class VAO {
public:
    struct LayoutElement {
        GLuint count;
        GLenum type;
        GLboolean normalized;
        GLuint size;
    };

    class Layout {
    public:
        void PushFloat(GLuint count) {
            m_elements.push_back(LayoutElement{ count, GL_FLOAT, GL_FALSE, static_cast<GLuint>(count * sizeof(float)) });
            m_stride += count * sizeof(float);
        }

        const std::vector<LayoutElement>& Elements() const { return m_elements; }
        GLuint Stride() const { return m_stride; }

    private:
        std::vector<LayoutElement> m_elements;
        GLuint m_stride = 0;
    };

public:
    VAO();
    ~VAO();

    void Bind() const;
    void Unbind() const;

    void ApplyLayout(const Layout& layout);

private:
    GLuint m_id = 0;
};
