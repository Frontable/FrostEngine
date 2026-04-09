#pragma once
#include "glad/glad.h"
#include <iostream>
#include <unordered_map>
#include "FrostMath.h"
namespace FrostEngine
{
    class Shader
    {
        public:

        Shader(unsigned int _id, const char* _vertexPath, const char* _fragmentPath);
        ~Shader();

        void SetUniformInt(const char* name, int value);
        void SetMatrix4x4(const char* name, const mat4& mat);

        void Bind();
        void Unbind();

        unsigned int ID() const { return m_shaderID; }

        private:

        unsigned int m_shaderID;
        const char* m_vertexPath;
        const char* m_fragmentPath;
        std::unordered_map<const char*, unsigned int> m_UniformMap;

        unsigned int GetUniformLocation(const char* name);
    };

}