#include "ScreenWrapSystem.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"

void ScreenWrapSystem::Update(float dt)
{
    auto& ecs = m_context.Get<FrostEngine::ECS>();

    for (Entity e : m_entities)
    {
        if (ecs.HasComponent<BulletTag>(e))
        {
            continue;
        }
        auto& transform = ecs.GetComponent<Transform2D>(e);
        vec2& pos = transform.position;

        float halfW = transform.scale.x * 0.5f;
        float halfH = transform.scale.y * 0.5f;

        if (pos.x + halfW < 0.0f)        pos.x = m_ScreenW + halfW;
        else if (pos.x - halfW > m_ScreenW) pos.x = -halfW;

        if (pos.y + halfH < 0.0f)        pos.y = m_ScreenH + halfH;
        else if (pos.y - halfH > m_ScreenH) pos.y = -halfH;
    }
}