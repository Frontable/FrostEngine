#include "Renderer/Renderer_GL.h"
#include "Renderer/RendererPrimitives.h"
#include "Resources/ResourceManager.h"

#include "glad/glad.h"
#include "Math/Math.h"
#include <vector>


namespace FrostEngine
{

    // abstraction on glClearColor to set the clearing color of the
    // COLOR_BUFFER_BIT buffer
    void Renderer_GL::RendererSetClearColor(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
    }

    void Renderer_GL::RendererSetClearColor(vec4 color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
    // abstraction on glClear()
    // will make it in the same way to accept a mask of integers
    // COLOR_BUFFER, STENCIL_BUFFER, DEPTH_BUFFER
    void Renderer_GL::RendererClear(unsigned int mask)
    {
        unsigned int glmask = 0;
        if (mask & COLOR_BUFFER)
            glmask |= GL_COLOR_BUFFER_BIT;
        if (mask & DEPTH_BUFFER)
            glmask |= GL_DEPTH_BUFFER_BIT;
        if (mask & STENCIL_BUFFER)
            glmask |= GL_STENCIL_BUFFER_BIT;

        if (glmask != 0)
            glClear(glmask);
    }

    // draw a basic colored quad at a given location and size
    void Renderer_GL::drawQuad(vec2 pos, vec2 size)
    {
        Shader& shader = *ResourceManager::GetShader("test");
        shader.Bind();        
        ArrayBuffer& vao = *RendererPrimitives::GetQuadVAO();   
        vao.Bind();
        mat4 projection = ortho(0, 1280, 720, 0);
        
        shader.SetMatrix4("uProjection", projection);
        
        mat4 model(1);
        mat4 trans = translate(vec3(pos.x, pos.y, 0.0));
        mat4 sca = scale(vec3(size.x, size.y, 1.0));
        mat4 modelaf = model * trans;
        mat4 models = modelaf * sca;
        //model = model * translate(vec3(pos.x, pos.y, 0.0));
        //model = scale(vec3(100,100,0));
        
        shader.SetMatrix4("uModel", models);

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    // draw a textured quad at a given location and size
    // void drawQuadTextured(vec2 pos, vec2 size, Texture2D tex);

    void Renderer_GL::AddShader()
    {
    }

}