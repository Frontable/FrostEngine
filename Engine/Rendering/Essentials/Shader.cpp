#include "Shader.h"

namespace FrostEngine
{
    Shader::Shader(unsigned int _id, const char *_vertexPath, const char *_fragmentPath)
    :m_shaderID{_id}, m_vertexPath{_vertexPath}, m_fragmentPath{_fragmentPath}
    {
    }

    Shader::~Shader()
    {

        if(m_shaderID > 0)
            glDeleteProgram(m_shaderID);
        printf("bomboclad\n");
    }

    void Shader::SetUniformInt(const char *name, int value)
    {
        glUniform1i(GetUniformLocation(name), value);
    }

    void Shader::SetUniformFloat(const char *name, float value)
    {
        glUniform1f(GetUniformLocation(name), value);
    }

    void Shader::SetMatrix4x4(const char *name, const mat4& mat)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
    }

    void Shader::Bind()
    {
        glUseProgram(m_shaderID);
    }

    void Shader::Unbind()
    {
        glUseProgram(0);
    }

    unsigned int Shader::GetUniformLocation(const char *name)
    {
        auto it = m_UniformMap.find(name);
        if(it != m_UniformMap.end())
            return it->second;

        unsigned int uniformLoc = glGetUniformLocation(m_shaderID, name);
        if(uniformLoc == GL_INVALID_INDEX)
        {
            printf("Invalid Uniform Location for shader %d\n", m_shaderID);
            return -1;
        }

        m_UniformMap.emplace(name, uniformLoc);
        return uniformLoc;
    }
}
