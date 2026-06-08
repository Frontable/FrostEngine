#pragma once
#include <ECS/SystemManager.h>
#include "SpriteBatchRenderer.h"
#include "Rendering/Essentials/Texture.h"
#include "Rendering/Essentials/Shader.h"

class RenderSystem : public ISystem
{
public:
    RenderSystem(Context& _context, SpriteBatchRenderer* renderer, float atlasW, float atlasH)
        : ISystem{ _context }, m_Renderer(renderer), m_AtlasW(atlasW), m_AtlasH(atlasH) {
    }

    void Update(float dt) override;

private:
    SpriteBatchRenderer* m_Renderer;
    float m_AtlasW, m_AtlasH;
};