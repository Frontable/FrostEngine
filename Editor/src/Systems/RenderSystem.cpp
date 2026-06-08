#include "RenderSystem.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"

void RenderSystem::Update(float dt)
{
    auto& ecs = m_context.Get<FrostEngine::ECS>();

    for (Entity e : m_entities)
    {
        auto& transform = ecs.GetComponent<Transform2D>(e);
        auto& sprite = ecs.GetComponent<Sprite>(e);

        // Skip if flickering and currently invisible
        if (ecs.HasComponent<Flicker>(e))
        {
            auto& flicker = ecs.GetComponent<Flicker>(e);
            if (!flicker.visible) continue;
        }

        m_Renderer->DrawSprite(
            { transform.position.x, transform.position.y, 0.0f },
            transform.scale,
            transform.rotation,
            sprite,
            m_AtlasW, m_AtlasH
        );
    }
}