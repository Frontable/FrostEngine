





#include "Shader.h"
#include <Logger/Logger.h>
#include <string>

Shader::Shader() noexcept {
    m_program = glCreateProgram();
    FROST_LOG("Shader program created (id={%u})", m_program);
}

Shader::~Shader() noexcept {
    if (m_program) {
        glDeleteProgram(m_program);
        FROST_LOG("Shader program deleted (id={%u})", m_program);
    }
}

void Shader::Compile(std::string_view vSrc, std::string_view fSrc) {
    if (vSrc.empty() || fSrc.empty()) {
        FROST_ERROR("Empty shader source passed to Compile()");
        return;
    }

    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vptr = vSrc.data();
    glShaderSource(vShader, 1, &vptr, nullptr);
    glCompileShader(vShader);
    checkCompileStatus(vShader, "VERTEX");

    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fptr = fSrc.data();
    glShaderSource(fShader, 1, &fptr, nullptr);
    glCompileShader(fShader);
    checkCompileStatus(fShader, "FRAGMENT");

    glAttachShader(m_program, vShader);
    glAttachShader(m_program, fShader);
    glLinkProgram(m_program);
    checkCompileStatus(m_program, "PROGRAM");

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    FROST_LOG("Shader compiled and linked (id={%u})", m_program);
}

Shader& Shader::Use() noexcept {
    glUseProgram(m_program);
    return *this;
}

void Shader::checkCompileStatus(GLuint obj, const char* type) {
    GLint success = 0;

    if (std::string(type) == "PROGRAM") {
        glGetProgramiv(obj, GL_LINK_STATUS, &success);
        if (!success) {
            char info[1024];
            glGetProgramInfoLog(obj, 1024, nullptr, info);
            FROST_ERROR("Shader program link error: {%s}", info);
        }
    }
    else {
        glGetShaderiv(obj, GL_COMPILE_STATUS, &success);
        if (!success) {
            char info[1024];
            glGetShaderInfoLog(obj, 1024, nullptr, info);
            FROST_ERROR("Shader compile error ({%s}): {%s}", type, info);
        }
    }
}
