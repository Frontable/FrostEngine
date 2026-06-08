#pragma once
#include <string>
#include "FontLoader.h"
#include "Rendering/Essentials/Shader.h"
#include "FrostMath.h"

namespace FrostEngine
{
    class TextRenderer
    {
    public:
        TextRenderer();
        ~TextRenderer();

        bool Init(const char* fontPath, unsigned int fontSize = 32);

        void RenderText(const std::string& text, float x, float y,
            float scale, const vec4& color, const mat4& projection);

    private:
        FontLoader   m_FontLoader;
        unsigned int m_VAO = 0;
        unsigned int m_VBO = 0;
        std::shared_ptr<Shader> m_Shader;
    };
}