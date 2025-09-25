





#pragma once
#include "glad/glad.h"

class Shader
{
public:

    unsigned int ID;

    Shader();
    ~Shader();

    void Compile(const char* vShaderSource, const char* fShaderSource);
    Shader& Use();

    private:

    void checkCompileStatus(unsigned int id, const char* type);

};