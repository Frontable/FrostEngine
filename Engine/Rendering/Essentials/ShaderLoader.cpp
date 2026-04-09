#include "ShaderLoader.h"
#include <iostream>
#include <fstream>
#include <string>

namespace FrostEngine
{
    std::shared_ptr<Shader> ShaderLoader::Create(const char *_vertexPath, const char *_fragmentPath)
    {
        unsigned int program = CreateProgram(_vertexPath, _fragmentPath);
        if(program)
        {
            return std::make_shared<Shader>(program, _vertexPath, _fragmentPath);
        }

        return nullptr;
    }

    unsigned int ShaderLoader::CreateProgram(const char *_vertexPath, const char *_fragmentPath)
    {
        const unsigned int program = glCreateProgram();
        const unsigned int vertex = Compile(GL_VERTEX_SHADER, _vertexPath);
        const unsigned int fragment = Compile(GL_FRAGMENT_SHADER, _fragmentPath);

        if(vertex == 0 || fragment == 0)
            return 0;
        
        if(!LinkShaders(program, vertex, fragment))
        {
            printf("Failed to link shaders\n");
            return 0;
        }

        return program;

    }

    unsigned int ShaderLoader::Compile(unsigned int _type, const char *_filePath)
    {
        const unsigned int shaderID = glCreateShader(_type);
        std::ifstream ifs(_filePath);
        if(ifs.fail())
        {
            printf("Failed to open file %s\n", _filePath);
            return 0;
        }
        std::string content, line;
        while(std::getline(ifs, line))
        {
            content += line + "\n";
        }
        ifs.close();

        const char* contentptr = content.c_str();

        glShaderSource(shaderID, 1, &contentptr, nullptr);
        glCompileShader(shaderID);

        if(!CompileSuccess(shaderID))
        {
            printf("Failed to compile shader %s\n", _filePath);
            return 0;
        }

        return shaderID;

    }

    bool ShaderLoader::CompileSuccess(unsigned int _shader)
    {
        int success;
        glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            char buff[512];
            glGetShaderInfoLog(_shader, 512, nullptr, buff);
            std::cout << "Failed to compile shader" << _shader << buff << std::endl;
            glDeleteShader(_shader);
            return false;
        }
        return true;
    }

    bool ShaderLoader::IsProgramValid(unsigned int _program)
    {
        int success;
        glGetProgramiv(_program, GL_LINK_STATUS, &success);
        if(!success)
        {
            char buff[512];
            glGetProgramInfoLog(_program, 512, nullptr, buff);
            std::cout << "Failed to link program" << _program << buff << std::endl;
            glDeleteProgram(_program);
            return false;
        }
        return true;
    }

    bool ShaderLoader::LinkShaders(unsigned int _program, unsigned int _vertexShader, unsigned int _fragmentShader)
    {
        glAttachShader(_program, _vertexShader);
        glAttachShader(_program, _fragmentShader);
        glLinkProgram(_program);
        if(!IsProgramValid(_program))
        {
            printf("Failed to link program");
            return false;
        }

        glDeleteShader(_vertexShader);
        glDeleteShader(_fragmentShader);
        return true;
    }
}
