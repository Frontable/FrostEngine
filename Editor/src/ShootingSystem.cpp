#include "ShootingSystem.h"
#include "ECS/ECS.h"
#include "Input.h"

void ShootingSystem::Update(float dt)
{

    auto &ecs = m_context.Get<FrostEngine::ECS>();
    for (auto &entity : m_entities)
    {

        if (!Input::IsKeyJustPressed(GLFW_KEY_SPACE))
            return;

        auto &playerTransform = ecs.GetComponent<Transform2D>(entity);

        vec2 forward{
            cos(playerTransform.rotation),
            sin(playerTransform.rotation)};

        Entity bullet = ecs.CreateEntity();

        ecs.AddComponent<Transform2D>(bullet, {playerTransform.position + forward * 25.0f,
                                               playerTransform.rotation,
                                               {8.0f, 8.0f}});

        ecs.AddComponent<Velocity2D>(bullet, {forward * 600.0f,
                                              0.0f});

        ecs.AddComponent<CircleCollider>(bullet, {4.0f});
        ecs.AddComponent<Lifetime>(bullet, {1.5f});
        ecs.AddComponent<BulletTag>(bullet, BulletTag());
    }
}