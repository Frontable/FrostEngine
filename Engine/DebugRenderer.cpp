#include "DebugRenderer.h"
#include <cmath>

namespace FrostEngine
{
    DebugRenderer::~DebugRenderer()
    {
        if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
        if (m_VBO) glDeleteBuffers(1, &m_VBO);
    }

    bool DebugRenderer::Init(const char* vFilePath, const char* fFilePath)
    {
        m_Shader = ShaderLoader::Create(vFilePath, fFilePath);

        if (!m_Shader) return false;

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Allocate enough for one circle worth of verts
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * CIRCLE_SEGMENTS, nullptr, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
        return true;
    }

    void DebugRenderer::DrawCircle(vec2 center, float radius, vec4 color)
    {
        m_Circles.push_back({ center, radius, color });
    }

    void DebugRenderer::Flush(const mat4& projection)
    {
        if (m_Circles.empty()) return;

        m_Shader->Bind();
        m_Shader->SetMatrix4x4("uProjection", projection);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_DEPTH_TEST);

        for (auto& circle : m_Circles)
        {
            // Build circle verts
            float verts[CIRCLE_SEGMENTS * 2];
            for (int i = 0; i < CIRCLE_SEGMENTS; i++)
            {
                float angle = (float)i / (float)CIRCLE_SEGMENTS * 2.0f * PI;
                verts[i * 2 + 0] = circle.center.x + cos(angle) * circle.radius;
                verts[i * 2 + 1] = circle.center.y + sin(angle) * circle.radius;
            }

            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);

            // Set color
            glUniform4f(glGetUniformLocation(m_Shader->ID(), "uColor"),
                circle.color.r, circle.color.g, circle.color.b, circle.color.a);

            glDrawArrays(GL_LINE_LOOP, 0, CIRCLE_SEGMENTS);
        }

        glEnable(GL_DEPTH_TEST); // ← restore after
        m_Circles.clear();
        glBindVertexArray(0);
    }
}