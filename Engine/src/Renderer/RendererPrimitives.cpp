#include "Renderer/RendererPrimitives.h"

namespace FrostEngine
{
    std::unique_ptr<ArrayBuffer> RendererPrimitives::s_QuadVAO = nullptr;
    std::unique_ptr<VertexBuffer> RendererPrimitives::s_QuadVBO = nullptr;
    std::unique_ptr<ArrayBuffer> RendererPrimitives::s_coloredQuadVAO = nullptr;
    std::unique_ptr<VertexBuffer> RendererPrimitives::s_coloredQuadVBO = nullptr;

    void RendererPrimitives::Init()
    {
        std::vector<Vertex> quadVertices =
        {   //pos          uv        color
            {-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
            { 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
            { 0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},

            { 0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
            {-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f},
            {-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f}
        };

        s_QuadVBO = std::make_unique<VertexBuffer>(quadVertices);

        s_QuadVBO->AddLayout({
            0,
            2,
            false,
            sizeof(Vertex),
            (const void*)offsetof(Vertex, x)
        });

        s_QuadVBO->AddLayout({
            1,
            2,
            false,
            sizeof(Vertex),
            (const void*)offsetof(Vertex, u)
        });

        s_QuadVBO->AddLayout({
            2,
            3,
            false,
            sizeof(Vertex),
            (const void*)offsetof(Vertex, r)
        });

        s_QuadVAO = std::make_unique<ArrayBuffer>();
        s_QuadVAO->AddBuffer(*s_QuadVBO);

        

    }

    void RendererPrimitives::Shutdown()
    {
        s_QuadVAO.reset();
        s_QuadVBO.reset();
    }

    ArrayBuffer* RendererPrimitives::GetQuadVAO()
    {
        return s_QuadVAO.get();
    }
}