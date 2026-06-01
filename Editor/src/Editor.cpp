#include "Editor.h"
#include "Rendering/Essentials/Vertex.h"
#include <typeindex>
#include "ECS/Components.h"
#include "ECS/ECS.h"
#include "MovementSystem.h"
#include "PlayerSystem.h"
#include "LifetimeSystem.h"
#include "ShootingSystem.h"
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
    loadSystems();
}
Editor::Editor(const char *_title, int _width, int _height)
    : Application{_title, _width, _height}
{
}

void Editor::Init()
{
    
}

void Editor::Input(float dt)
{
    
}

void Editor::Update(float dt)
{
    
    
    
}

void Editor::Render(float dt)
{
    m_Shader->Bind();
    auto camera = m_MainContext.Get<FrostEngine::Camera2D>();
    camera.Update();
    m_Shader->SetMatrix4x4("uProjection", camera.GetCameraMatrix());

    m_Shader->SetUniformInt("useTexture", false);
    //ren->DrawSprite({200,200}, {200,200}, {{24,24}, {200,200}});
    
    m_Shader->SetUniformInt("useTexture", true);
    glActiveTexture(GL_TEXTURE0);
    m_Shader->SetUniformInt("tex", 0);
    m_Texture->Bind();
    float size = 1024;
    float u = 0.0f/1024.0f;
    float v = 410.0f/1024.0f;
    float uw = 612.0f/1024.0f;
    float vh = 600.0f/1024.0f;
    
    if(Input::IsKeyPressed(GLFW_KEY_Q))
    {
        rotate = -10 * dt;
    }
    
    if(Input::IsKeyPressed(GLFW_KEY_S))
    {
        pos.y -= 10;
    }
    if(Input::IsKeyPressed(GLFW_KEY_W))
    {
        pos.y += 10;
    }
    m_Renderer->DrawSprite({400,400}, {60,60}, rotate, {{pos.x, pos.y}, {250, 250}}, 1024, 1024);

    m_Renderer->Render();
}

void Editor::Clean()
{
}



void Editor::loadSystems()
{
    auto& ecs = m_MainContext.Get<FrostEngine::ECS>();

    ecs.RegisterSystem<MovementSystem>(m_MainContext);
    Signature moveSignature;
    moveSignature.set(ecs.GetComponentID<Transform2D>() | ecs.GetComponentID<Velocity2D>());
    ecs.SetSystemSignature<MovementSystem>(moveSignature);

    ecs.RegisterSystem<ShootingSystem>(m_MainContext);
    Signature shootSignature;
    shootSignature.set(ecs.GetComponentID<Transform2D>() | ecs.GetComponentID<Velocity2D>() | ecs.GetComponentID<PlayerTag>());
    ecs.SetSystemSignature<MovementSystem>(shootSignature);

    ecs.RegisterSystem<PlayerSystem>(m_MainContext);
    Signature playerSignature;
    playerSignature.set(ecs.GetComponentID<Transform2D>() | ecs.GetComponentID<Velocity2D>() | ecs.GetComponentID<PlayerTag>());
    ecs.SetSystemSignature<MovementSystem>(playerSignature);

    ecs.RegisterSystem<LifetimeSystem>(m_MainContext);
    Signature lifeSignature;
    lifeSignature.set(ecs.GetComponentID<Lifetime>());
    ecs.SetSystemSignature<MovementSystem>(lifeSignature);

}