#include "CollisionSystem.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include <cmath>

static bool CirclesOverlap(const vec2& posA, float rA, const vec2& posB, float rB)
{
    float dx = posA.x - posB.x;
    float dy = posA.y - posB.y;
    float distSq = dx * dx + dy * dy;
    float radSum = rA + rB;
    return distSq < radSum * radSum;
}

void CollisionSystem::Update(float dt)
{
    auto& ecs = m_context.Get<FrostEngine::ECS>();
    std::vector<Entity> entities = m_entities;

    for (size_t i = 0; i < entities.size(); i++)
    {
        for (size_t j = i + 1; j < entities.size(); j++)
        {
            Entity a = entities[i];
            Entity b = entities[j];

            // Skip if either entity is still immune
            if (ecs.HasComponent<SpawnImmunity>(a) || ecs.HasComponent<SpawnImmunity>(b))
                continue;

            auto& tA = ecs.GetComponent<Transform2D>(a);
            auto& cA = ecs.GetComponent<CircleCollider>(a);
            auto& tB = ecs.GetComponent<Transform2D>(b);
            auto& cB = ecs.GetComponent<CircleCollider>(b);

            if (CirclesOverlap(tA.position, cA.radius, tB.position, cB.radius))
                ecs.RegisterEvent(a, b);
        }
    }
}