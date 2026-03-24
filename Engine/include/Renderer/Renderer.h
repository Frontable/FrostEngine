#pragma once
#include "RendererAPI.h"
#include "Math/Math.h"



namespace FrostEngine
{
    class Renderer
{
public:
    static void Init();
    static void Shutdown();

    static void RendererSetClearColor(float r, float g, float b, float a);
    static void RendererSetClearColor(const vec4& color);
    static void RendererClear(unsigned int mask);
    static void DrawQuad(const vec2& pos, const vec2& size);

private:
    static RendererAPI* s_renderer;
};
}