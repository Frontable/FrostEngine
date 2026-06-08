#include "ShootingSystem.h"
#include "ECS/ECS.h"
#include "Input.h"
#include "../SpriteSheet.h"

void ShootingSystem::Update(float dt)
{
    auto& ecs = m_context.Get<FrostEngine::ECS>();
    for (auto& entity : m_entities)
    {
        if (!Input::IsKeyJustPressed(GLFW_KEY_SPACE))
            continue;  // ← was return

        auto& playerTransform = ecs.GetComponent<Transform2D>(entity);

        vec2 forward{
        cos(playerTransform.rotation - PI / 2.0f),  // ← same offset
        sin(playerTransform.rotation - PI / 2.0f)
        };

        Entity bullet = ecs.CreateEntity();

        ecs.AddComponent<Transform2D>(bullet, { playerTransform.position + forward * 25.0f,
                                               playerTransform.rotation,
                                               {20.0f, 20.0f} });
        ecs.AddComponent<Velocity2D>(bullet, { forward * 600.0f, 0.0f });
        ecs.AddComponent<Sprite>(bullet, GetSprite(SpriteID::PLAYER_BULLET));
        ecs.AddComponent<CircleCollider>(bullet, { 4.0f });
        ecs.AddComponent<Lifetime>(bullet, { 1.5f });
        ecs.AddComponent<SpawnImmunity>(bullet, { 0.1f });
        ecs.AddComponent<BulletTag>(bullet, BulletTag());
    }
}