#include "Renderer/Renderer.h"

#include "Renderer/Renderer_GL.h"

#include "glad/glad.h"
#include "Math/Math.h"
#include <vector>

namespace FrostEngine
{
    RendererAPI *Renderer::s_renderer = nullptr;

    void Renderer::Init()
    {
        if (!s_renderer)
            s_renderer = new Renderer_GL();
    }

    void Renderer::Shutdown()
    {
        delete s_renderer;
        s_renderer = nullptr;
    }

    void Renderer::RendererSetClearColor(float r, float g, float b, float a)
    {
        s_renderer->RendererSetClearColor(r, g, b, a);
    }

    void Renderer::RendererClear(unsigned int mask)
    {
        s_renderer->RendererClear(mask);
    }

    
    void Renderer::DrawQuad(const vec2& pos, const vec2& size)
    {
        s_renderer->drawQuad(pos, size);
    }

}