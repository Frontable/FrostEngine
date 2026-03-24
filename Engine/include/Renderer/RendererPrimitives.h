#pragma once
#include "Renderer/VertexArray.h"
#include <memory>

namespace FrostEngine
{
    class RendererPrimitives
    {
    public:
        static void Init();
        static void Shutdown();

        static ArrayBuffer* GetQuadVAO();

    private:
        static std::unique_ptr<ArrayBuffer> s_QuadVAO;
        static std::unique_ptr<VertexBuffer> s_QuadVBO;

        static std::unique_ptr<ArrayBuffer> s_coloredQuadVAO;
        static std::unique_ptr<VertexBuffer> s_coloredQuadVBO;
    };
}