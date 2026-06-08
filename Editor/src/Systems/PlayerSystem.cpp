#include "PlayerSystem.h"
#include "Input.h"
#include "FrostMath.h"
#include "ECS/ECS.h"

void PlayerSystem::Update(float dt)
{
    IsThrusting = false;

    if (Input::IsKeyPressed(GLFW_KEY_W))
    {
        IsThrusting = true;
        auto& ecs = m_context.Get<FrostEngine::ECS>();

        constexpr float rotateSpeed = 3.0f;
        constexpr float thrust = 400.0f;
        constexpr float maxSpeed = 800.0f;  // ← add this
        constexpr float drag = 0.98f;       // ← slightly stronger drag

        for (auto& entity : m_entities)
        {
            auto& transform = ecs.GetComponent<Transform2D>(entity);
            auto& velocity = ecs.GetComponent<Velocity2D>(entity);

            if (Input::IsKeyPressed(GLFW_KEY_A))
                transform.rotation -= rotateSpeed * dt;

            if (Input::IsKeyPressed(GLFW_KEY_D))
                transform.rotation += rotateSpeed * dt;

            if (Input::IsKeyPressed(GLFW_KEY_W))
            {
                vec2 forward{
                    cos(transform.rotation - PI / 2.0f),  // ← offset by -90 degrees
                    sin(transform.rotation - PI / 2.0f)
                };

                velocity.velocity.x += forward.x * thrust * dt;
                velocity.velocity.y += forward.y * thrust * dt;
            }

            // Apply drag
            velocity.velocity.x *= drag;
            velocity.velocity.y *= drag;

            // Clamp to max speed
            float speedSq = velocity.velocity.x * velocity.velocity.x
                + velocity.velocity.y * velocity.velocity.y;

            if (speedSq > maxSpeed * maxSpeed)
            {
                float speed = std::sqrt(speedSq);
                velocity.velocity.x = (velocity.velocity.x / speed) * maxSpeed;
                velocity.velocity.y = (velocity.velocity.y / speed) * maxSpeed;
            }
        }
    }
    
}