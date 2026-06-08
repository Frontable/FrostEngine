#include "FlickerSystem.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"

void FlickerSystem::Update(float dt)
{
    auto& ecs = m_context.Get<FrostEngine::ECS>();

    for (Entity e : m_entities)
    {
        auto& flicker = ecs.GetComponent<Flicker>(e);

        flicker.timer += dt;
        if (flicker.timer >= flicker.interval)
        {
            flicker.timer = 0.0f;
            flicker.visible = !flicker.visible;
        }
    }
}