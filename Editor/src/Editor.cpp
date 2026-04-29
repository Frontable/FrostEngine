#include "Editor.h"
#include "Rendering/Essentials/Vertex.h"
#include <typeindex>
#include "ECS/Components.h"
#include "ECS/ECS.h"
#include "Systems/RenderingSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/DamageSystem.h"
#include "Input.h"

struct UVs
{
    float u, v, width, height;

    UVs()
        : u(0.f), v(0.f), width(0.f), height(0.f)
    {
    }
};

Editor::Editor()
    : Editor("default", 800, 600)
{
}
Editor::Editor(const char *_title, int _width, int _height)
    : Application{_title, _width, _height}
{
}

void Editor::Init()
{

    auto e1 = m_ecs.CreateEntity(FrostEngine::EntityManager::Type::PLAYER);
    auto e2 = m_ecs.CreateEntity(FrostEngine::EntityManager::Type::ENEMY);
    m_ecs.AddComponent(e1, Transform2D{vec2{100, 100}, 0, vec2{100}});
    m_ecs.AddComponent(e1, RigidBody2D{vec2{100}, 10});
    m_ecs.AddComponent(e1, Sprite{
                               Vertexx{vec4{1}, vec2{1}},
                               Vertexx{vec4{1}, vec2{1}},
                               Vertexx{vec4{1}, vec2{1}},
                               Vertexx{vec4{1}, vec2{1}}});
    m_ecs.AddComponent(e1, BoxCollider{});

    m_ecs.AddComponent(e2, Transform2D{vec2{500, 100}, 0, vec2{90}});
    m_ecs.AddComponent(e2, RigidBody2D{vec2{100}, 10});
    m_ecs.AddComponent(e2, Sprite{
                               Vertexx{vec4{1}, vec2{1}},
                               Vertexx{vec4{1}, vec2{1}},
                               Vertexx{vec4{1}, vec2{1}},
                               Vertexx{vec4{1}, vec2{1}}});
    m_ecs.AddComponent(e2, BoxCollider{});

    float startX = 100.0f;
    float startY = 100.0f;

    float spacingX = 100.0f;
    float spacingY = 100.0f;

    int rows = 50;
    int cols = 10;

    for (int y = 0; y < rows; y++)
    {
        for (int x = 0; x < cols; x++)
        {
            auto e = m_ecs.CreateEntity(FrostEngine::EntityManager::Type::ENEMY);

            vec2 position = {
                startX + x * spacingX,
                startY + y * spacingY};

            m_ecs.AddComponent(e, Transform2D{position, 0, vec2{10, 10}});
            m_ecs.AddComponent(e, RigidBody2D{vec2{10, 10}, 10});
            m_ecs.AddComponent(e, BoxCollider{});

            m_ecs.AddComponent(e, Sprite{
                                      Vertexx{vec4{1}, vec2{1}},
                                      Vertexx{vec4{1}, vec2{1}},
                                      Vertexx{vec4{1}, vec2{1}},
                                      Vertexx{vec4{1}, vec2{1}}});
        }
    }
}

void Editor::Input()
{
}

void Editor::Update()
{
    auto &phys = m_ecs.getSystem<PhysicsSystem>();
    phys.m_window = this->m_window.get();
    phys.Update();
    auto &col = m_ecs.getSystem<CollisionSystem>();
    col.Update();
    if (Input::IsKeyJustPressed(GLFW_KEY_D))
    {
        printf("D\n");
    }
    if (Input::IsKeyJustReleased(GLFW_KEY_D))
    {
        printf("d\n");
    }

    auto &damageSys = m_ecs.getSystem<DamageSystem>();
    damageSys.Update();
    m_ecs.fortest();
}

void Editor::Render()
{
    auto &ren = m_ecs.getSystem<RenderingSystem>();
    ren.Update();
}

void Editor::Clean()
{
}
