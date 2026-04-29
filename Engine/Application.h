#pragma once
#include "Window.h"
#include "Rendering/Essentials/Shader.h"
#include "Rendering/Essentials/Texture.h"
#include <memory>
#include "ECS/ECS.h"
#include "Rendering/Core/Camera2D.h"
#include "Context.h"



class Application
{
public:
    Application();
    Application(const char *_title, int _width, int _height);
    virtual ~Application();

    void Run();

    virtual void Init() = 0;
    virtual void Input() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Clean() = 0;

protected:
    bool m_isRunning;
    const char *m_title;
    int m_width, m_height;
    Context m_mainContext;

    std::unique_ptr<FROST_RENDERING::Window> m_window;
    FrostEngine::ECS &m_ecs = FrostEngine::ECS::get();
    std::shared_ptr<FrostEngine::Camera2D> m_camera;
};