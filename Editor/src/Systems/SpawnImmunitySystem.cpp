#include "SpawnImmunitySystem.h"
#include "ECS/ECS.h"

void SpawnImmunitySystem::Update(float dt)
{
    auto& ecs = m_context.Get<FrostEngine::ECS>();
    std::vector<Entity> toRemove;

    for (Entity e : m_entities)
    {
        auto& immunity = ecs.GetComponent<SpawnImmunity>(e);
        immunity.timeLeft -= dt;
        if (immunity.timeLeft <= 0.0f)
            toRemove.push_back(e);
    }

    for (Entity e : toRemove)
        ecs.RemoveComponent<SpawnImmunity>(e);
}