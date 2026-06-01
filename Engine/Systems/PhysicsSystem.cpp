// #include "PhysicsSystem.h"
// #include "ECS/ECS.h"
// #include "glfw/glfw3.h"
// #include <cmath>
// #include "Input.h"
// #include "Window.h"

// void PhysicsSystem::Update()
// {
//     auto &m_ecs = m_context.Get<FrostEngine::ECS>();
//     auto &window = m_context.Get<FROST_RENDERING::Window>();
//     constexpr float WINDOW_WIDTH = 800.0f;
//     constexpr float WINDOW_HEIGHT = 600.0f;
//     constexpr float RESPAWN_X = 800.0f;
//     constexpr float EPSILON = 0.01f;
    
//     //temp for 1st entity only
    
//         auto& trans = m_ecs.GetComponent<Transform2D>(m_entities[0]);
//         auto& rigid = m_ecs.GetComponent<RigidBody2D>(m_entities[0]);
        
//         // Gravity
//         // if(rigid.falling)
//         // {
//         //     trans.position.y += rigid.gravity;
//         // }
        
//         // Ground collision
//         float entityBottom = trans.position.y + (trans.size.y / 2);
//         if(std::abs(entityBottom - WINDOW_HEIGHT) < EPSILON || entityBottom >= WINDOW_HEIGHT)
//         {
//             rigid.falling = false;
//             trans.position.y = WINDOW_HEIGHT - trans.size.y / 2;
//         }
        
//         // Wall collision (right side)
//         float entityRight = trans.position.x + (trans.size.x / 2);
//         if(std::abs(entityRight - WINDOW_WIDTH) < EPSILON || entityRight >= WINDOW_WIDTH)
//         {
//             trans.position.x = RESPAWN_X - trans.size.x / 2;
//         }
        
//         // Input handling - should probably be in separate InputSystem
//         //auto* window = window->Handle();
        
//         if(Input::IsKeyJustPressed(GLFW_KEY_A))
//         {
//             trans.position.x -= rigid.velocity.x;
//         }
//         if(Input::IsKeyJustPressed(GLFW_KEY_D))
//         {
//             trans.position.x += rigid.velocity.x;
//         }
//         if(Input::IsKeyJustPressed(GLFW_KEY_W))
//         {
//             trans.position.y -= rigid.velocity.y; // Fixed: move up
//         }
//         if(Input::IsKeyJustPressed(GLFW_KEY_S))
//         {
//             trans.position.y += rigid.velocity.y; // Fixed: move down
        
//     }

//     // for(auto& entity : m_entities)
//     // {
//     //     auto& trans = m_ecs.GetComponent<Transform2D>(entity);
//     //     auto& rigid = m_ecs.GetComponent<RigidBody2D>(entity);
        
//     //     // Gravity
//     //     if(rigid.falling)
//     //     {
//     //         trans.position.y += rigid.gravity;
//     //     }
        
//     //     // Ground collision
//     //     float entityBottom = trans.position.y + (trans.size.y / 2);
//     //     if(std::abs(entityBottom - WINDOW_HEIGHT) < EPSILON || entityBottom >= WINDOW_HEIGHT)
//     //     {
//     //         rigid.falling = false;
//     //         trans.position.y = WINDOW_HEIGHT - trans.size.y / 2;
//     //     }
        
//     //     // Wall collision (right side)
//     //     float entityRight = trans.position.x + (trans.size.x / 2);
//     //     if(std::abs(entityRight - WINDOW_WIDTH) < EPSILON || entityRight >= WINDOW_WIDTH)
//     //     {
//     //         trans.position.x = RESPAWN_X - trans.size.x / 2;
//     //     }
        
//     //     // Input handling - should probably be in separate InputSystem
//     //     auto* window = window->Handle();
        
//     //     if(Input::IsKeyJustPressed(GLFW_KEY_A))
//     //     {
//     //         trans.position.x -= rigid.velocity.x;
//     //     }
//     //     if(Input::IsKeyJustPressed(GLFW_KEY_D))
//     //     {
//     //         trans.position.x += rigid.velocity.x;
//     //     }
//     //     if(Input::IsKeyJustPressed(GLFW_KEY_W))
//     //     {
//     //         trans.position.y += rigid.velocity.y; // Fixed: move up
//     //     }
//     //     if(Input::IsKeyJustPressed(GLFW_KEY_S))
//     //     {
//     //         trans.position.y -= rigid.velocity.y; // Fixed: move down
//     //     }
//     // }
// }