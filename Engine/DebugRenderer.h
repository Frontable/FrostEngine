#pragma once
#include <glad/glad.h>
#include <vector>
#include "FrostMath.h"
#include "Rendering/Essentials/Shader.h"
#include "Rendering/Essentials/ShaderLoader.h"

namespace FrostEngine
{
    class DebugRenderer
    {
    public:
        DebugRenderer() = default;
        ~DebugRenderer();

        bool Init(const char* vFilePath, const char* fFilePath);
        void DrawCircle(vec2 center, float radius, vec4 color = { 0.0f, 1.0f, 0.0f, 1.0f });
        void Flush(const mat4& projection);

    private:
        struct CircleData
        {
            vec2  center;
            float radius;
            vec4  color;
        };

        std::vector<CircleData> m_Circles;
        std::shared_ptr<Shader> m_Shader;
        unsigned int m_VAO = 0;
        unsigned int m_VBO = 0;

        static constexpr int CIRCLE_SEGMENTS = 32;
    };
}