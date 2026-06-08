#include "LifetimeSystem.h"
#include "ECS/ECS.h"

void LifetimeSystem::Update(float dt)
{
    std::vector<Entity> toDestroy;
    auto& ecs = m_context.Get<FrostEngine::ECS>();
    for (Entity e : m_entities)
    {
        auto& lifetime = ecs.GetComponent<Lifetime>(e);

        lifetime.timeLeft -= dt;

        if (lifetime.timeLeft <= 0.0f)
            toDestroy.push_back(e);
    }

    for (Entity e : toDestroy)
        ecs.DeleteEntity(e);
}