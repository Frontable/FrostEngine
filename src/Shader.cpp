






#include "Shader.h"
#include <iostream>


Shader::Shader()
{
    ID = glCreateProgram();
}

Shader::~Shader()
{

}

Shader& Shader::Use()
{
    glUseProgram(ID);
    return *this;
}


void Shader::Compile(const char* vShaderSource, const char* fShaderSource)
{
    unsigned int vShader, fShader;
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vShaderSource, NULL);
    glCompileShader(vShader);
    checkCompileStatus(vShader, "VERTEX");
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fShaderSource, NULL);
    glCompileShader(fShader);
    checkCompileStatus(fShader, "FRAGMENT");

    glAttachShader(ID, vShader);
    glAttachShader(ID, fShader);
    glLinkProgram(ID);
    checkCompileStatus(ID, "PROGRAM");

    glDeleteShader(vShader);
    glDeleteShader(fShader);

}

void Shader::checkCompileStatus(unsigned int id, const char* type)
{

    int success;
    char infoLog[1024];


    if(type != "PROGRAM")
    {
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(id, 1024, 0, infoLog);
            std::cout<<"Failed to COMPILE " << type << " SHADER " << infoLog <<std::endl;
        }
    }else
    {
        glGetProgramiv(id, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(id, 1024, 0, infoLog);
            std::cout<<"Failed to LINK " << type << infoLog <<std::endl;
        }
    }


}