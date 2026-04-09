#pragma once
#include <memory>
#include "Shader.h"

namespace FrostEngine
{
    class ShaderLoader
    {
        public:
            ShaderLoader() = delete;
            static std::shared_ptr<Shader> Create(const char* _vertexPath, const char* _fragmentPath);
    
        private:
            static unsigned int CreateProgram(const char* _vertexPath, const char* _fragmentPath);
            static unsigned int Compile(unsigned int _type, const char* _filePath);
            static bool CompileSuccess(unsigned int _shader);
            static bool IsProgramValid(unsigned int _program);
            static bool LinkShaders(unsigned int _program, unsigned int _vertexShader, unsigned int _fragmentShader);
    };
}