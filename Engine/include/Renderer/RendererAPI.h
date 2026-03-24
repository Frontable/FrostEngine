#pragma once

#include "Math/Math.h"

const unsigned int COLOR_BUFFER = 1 << 0;
const unsigned int DEPTH_BUFFER = 1 << 1;
const unsigned int STENCIL_BUFFER = 1 << 2;

namespace FrostEngine
{
    // virtual class renderer that will be expanded to gl renderer or vulkan renderer
    class RendererAPI
    {
        public:
        virtual ~RendererAPI() = default;
        // abstraction on glClearColor to set the clearing color of the
        // COLOR_BUFFER_BIT buffer
        virtual void RendererSetClearColor(float r, float g, float b, float a) = 0;
        virtual void RendererSetClearColor(vec4 color) = 0;
        // abstraction on glClear()
        // will make it in the same way to accept a mask of integers
        // COLOR_BUFFER, STENCIL_BUFFER, DEPTH_BUFFER
        virtual void RendererClear(unsigned int mask) = 0;

        // draw a basic colored quad at a given location and size
        virtual void drawQuad(vec2 pos, vec2 size) = 0;

        // draw a textured quad at a given location and size
        // void drawQuadTextured(vec2 pos, vec2 size, Texture2D tex);

        virtual void AddShader() = 0; // to add a shader to the vector
    private:
        // vector that will store shaders for ease of use with each command
        // each shader will have a id and a const char* name
        // std::vector<Shader> m_Shaders;
    };
}
