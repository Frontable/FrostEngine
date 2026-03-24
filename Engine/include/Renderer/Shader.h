#pragma once
#include "Math/Math.h"
#include <string>

namespace FrostEngine
{
    class Shader
    {
    public:
        Shader();
        ~Shader();

        Shader(const Shader&) = delete;
        Shader& operator=(const Shader&) = delete;

        Shader(Shader&& other) noexcept;
        Shader& operator=(Shader&& other) noexcept;

        bool CreateFromSource(const char* vShaderSource, const char* fShaderSource);
        bool CreateFromFile(const char* vShaderPath, const char* fShaderPath);

        void Destroy();

        void Bind() const;
        void Unbind() const;

        void SetInt(const char* name, int value);
        void SetFloat(const char* name, float value);
        void SetVec2(const char* name, float x, float y);
        void SetVec2(const char* name, vec2 vec);
        void SetVec3(const char* name, float x, float y, float z);
        void SetVec3(const char* name, vec3 vec);
        void SetMatrix4(const char* name, mat4 mat);

        unsigned int ID() const { return m_id; }
        bool IsValid() const { return m_id != 0; }

    private:
        unsigned int m_id;
    };
}