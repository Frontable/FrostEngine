#include "Renderer/Shader.h"
#include "Core/Logger.h"
#include "glad/glad.h"

#include <cstring>
#include <fstream>
#include <sstream>
#include <string>

static bool checkShaderCompileStatus(unsigned int shader, const char* shaderType);
static bool checkProgramLinkStatus(unsigned int program);
static bool readFileToString(const char* path, std::string& outSource);

namespace FrostEngine
{
    Shader::Shader()
        : m_id(0)
    {
    }

    Shader::~Shader()
    {
        Destroy();
    }

    Shader::Shader(Shader&& other) noexcept
        : m_id(other.m_id)
    {
        other.m_id = 0;
    }

    Shader& Shader::operator=(Shader&& other) noexcept
    {
        if (this == &other)
            return *this;

        Destroy();

        m_id = other.m_id;
        other.m_id = 0;

        return *this;
    }

    void Shader::Destroy()
    {
        if (m_id)
        {
            glDeleteProgram(m_id);
            m_id = 0;
        }
    }

    bool Shader::CreateFromSource(const char* vShaderSource, const char* fShaderSource)
    {
        Destroy();

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        unsigned int program = glCreateProgram();

        glShaderSource(vertexShader, 1, &vShaderSource, nullptr);
        glCompileShader(vertexShader);
        if (!checkShaderCompileStatus(vertexShader, "VERTEX"))
        {
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glDeleteProgram(program);
            return false;
        }

        glShaderSource(fragmentShader, 1, &fShaderSource, nullptr);
        glCompileShader(fragmentShader);
        if (!checkShaderCompileStatus(fragmentShader, "FRAGMENT"))
        {
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glDeleteProgram(program);
            return false;
        }

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        if (!checkProgramLinkStatus(program))
        {
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            glDeleteProgram(program);
            return false;
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        m_id = program;

        FROST_LOG("Shader created successfully");
        return true;
    }

    bool Shader::CreateFromFile(const char* vShaderPath, const char* fShaderPath)
    {
        std::string vertexSource;
        std::string fragmentSource;

        if (!readFileToString(vShaderPath, vertexSource))
        {
            FROST_WARN("Failed to read vertex shader file:", vShaderPath);
            return false;
        }

        if (!readFileToString(fShaderPath, fragmentSource))
        {
            FROST_WARN("Failed to read fragment shader file:", fShaderPath);
            return false;
        }

        return CreateFromSource(vertexSource.c_str(), fragmentSource.c_str());
    }

    void Shader::Bind() const
    {
        glUseProgram(m_id);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }

    void Shader::SetInt(const char* name, int value)
    {
        int location = glGetUniformLocation(m_id, name);
        if (location != -1)
            glUniform1i(location, value);
    }

    void Shader::SetFloat(const char* name, float value)
    {
        int location = glGetUniformLocation(m_id, name);
        if (location != -1)
            glUniform1f(location, value);
    }

    void Shader::SetVec2(const char* name, float x, float y)
    {
        int location = glGetUniformLocation(m_id, name);
        if (location != -1)
            glUniform2f(location, x, y);
    }

    void Shader::SetVec2(const char* name, vec2 vec)
    {
        SetVec2(name, vec.x, vec.y);
    }

    void Shader::SetVec3(const char* name, float x, float y, float z)
    {
        int location = glGetUniformLocation(m_id, name);
        if (location != -1)
            glUniform3f(location, x, y, z);
    }

    void Shader::SetVec3(const char* name, vec3 vec)
    {
        SetVec3(name, vec.x, vec.y, vec.z);
    }

    void Shader::SetMatrix4(const char* name, mat4 mat)
    {
        int location = glGetUniformLocation(m_id, name);
        if (location != -1)
            glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }
}

static bool checkShaderCompileStatus(unsigned int shader, const char* shaderType)
{
    int success = 0;
    char infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        FROST_WARN("Failed to compile shader:", shaderType, infoLog);
        return false;
    }

    return true;
}

static bool checkProgramLinkStatus(unsigned int program)
{
    int success = 0;
    char infoLog[512];

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        FROST_WARN("Failed to link shader program:", infoLog);
        return false;
    }

    return true;
}

static bool readFileToString(const char* path, std::string& outSource)
{
    std::ifstream file(path);
    if (!file.is_open())
        return false;

    std::stringstream buffer;
    buffer << file.rdbuf();
    outSource = buffer.str();
    return true;
}