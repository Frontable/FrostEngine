#include "PlayerSystem.h"
#include "Input.h"
#include "FrostMath.h"
#include "ECS/ECS.h"

void PlayerSystem::Update(float dt)
{
    auto &ecs = m_context.Get<FrostEngine::ECS>();

    //There is only one entity with the player tag created so in this system there should only be one entity as well.
    for (auto &entity : m_entities)
    {
        auto &transform = ecs.GetComponent<Transform2D>(entity);
        auto &velocity = ecs.GetComponent<Velocity2D>(entity);

        constexpr float rotateSpeed = 4.0f;
        constexpr float thrust = 300.0f;

        if (Input::IsKeyPressed(GLFW_KEY_A))
            transform.rotation -= rotateSpeed * dt;

        if (Input::IsKeyPressed(GLFW_KEY_D))
            transform.rotation += rotateSpeed * dt;

        if (Input::IsKeyPressed(GLFW_KEY_W))
        {
            vec2 forward{
                cos(transform.rotation),
                sin(transform.rotation)};

            velocity.velocity += forward * thrust * dt;
        }

        velocity.velocity *= 0.99f; // simple drag
    }
}