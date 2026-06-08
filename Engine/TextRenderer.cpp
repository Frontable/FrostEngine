#include "TextRenderer.h"
#include "Rendering/Essentials/ShaderLoader.h"
#include <glad/glad.h>
#include <iostream>

namespace FrostEngine
{
    TextRenderer::TextRenderer() {}

    TextRenderer::~TextRenderer()
    {
        if (m_VAO) glDeleteVertexArrays(1, &m_VAO);
        if (m_VBO) glDeleteBuffers(1, &m_VBO);
    }

    bool TextRenderer::Init(const char* fontPath, unsigned int fontSize)
    {
        if (!m_FontLoader.Load(fontPath, fontSize))
            return false;

        m_Shader = ShaderLoader::Create(
            "D:/Projects/FrostEngine/data/Shaders/textV.glsl",
            "D:/Projects/FrostEngine/data/Shaders/textF.glsl"
        );

        if (!m_Shader)
        {
            std::cout << "[TextRenderer] Failed to load text shaders\n";
            return false;
        }

        // Each quad = 6 verts * (x, y, u, v)
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return true;
    }

    void TextRenderer::RenderText(const std::string& text, float x, float y,
        float scale, const vec4& color, const mat4& projection)
    {
        m_Shader->Bind();
        m_Shader->SetMatrix4x4("uProjection", projection);
        m_Shader->SetUniformFloat("textColor", 0); // see note below
        glUniform4f(glGetUniformLocation(m_Shader->ID(), "textColor"),
            color.r, color.g, color.b, color.a);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_FontLoader.GetAtlasID());
        m_Shader->SetUniformInt("text", 0);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindVertexArray(m_VAO);

        float cursorX = x;

        for (char c : text)
        {
            if (c < 32 || c >= 128) continue;

            const Glyph& g = m_FontLoader.GetGlyph(c);

            float xpos = cursorX + g.bearing.x * scale;
            float ypos = y + (m_FontLoader.GetFontSize() - g.bearing.y) * scale;
            float w = g.size.x * scale;
            float h = g.size.y * scale;

            // 6 verts, each (x, y, u, v)
            float verts[6][4] = {
                { xpos,     ypos + h, g.uvMin.x, g.uvMax.y },
                { xpos,     ypos,     g.uvMin.x, g.uvMin.y },
                { xpos + w, ypos,     g.uvMax.x, g.uvMin.y },

                { xpos,     ypos + h, g.uvMin.x, g.uvMax.y },
                { xpos + w, ypos,     g.uvMax.x, g.uvMin.y },
                { xpos + w, ypos + h, g.uvMax.x, g.uvMax.y },
            };

            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts);

            glDrawArrays(GL_TRIANGLES, 0, 6);
            cursorX += g.advance * scale;
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}