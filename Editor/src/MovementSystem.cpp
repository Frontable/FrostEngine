#include "MovementSystem.h"
#include "ECS/ECS.h"

void MovementSystem::Update(float dt)
{
    auto& ecs = m_context.Get<FrostEngine::ECS>();
    for (Entity e : m_entities)
    {
        auto& transform = ecs.GetComponent<Transform2D>(e);
        auto& velocity = ecs.GetComponent<Velocity2D>(e);

        transform.position += velocity.velocity * dt;
        transform.rotation += velocity.angularVelocity * dt;
    }
}