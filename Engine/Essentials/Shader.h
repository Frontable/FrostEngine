#pragma once
#include <string_view>
#include <glad/glad.h>

class Shader {
public:
    Shader() noexcept;
    ~Shader() noexcept;

    void Compile(std::string_view vertexSrc, std::string_view fragmentSrc);
    Shader& Use() noexcept;

    GLuint ID() const noexcept { return m_program; }

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader(Shader&&) noexcept = default;
    Shader& operator=(Shader&&) noexcept = default;

private:
    GLuint m_program{0};
    void checkCompileStatus(GLuint obj, const char* type);
};
