#include "Application.h"
#include "glad/glad.h"
#include "Context.h"
#include "ScriptSystem.h"
#include "RenderSystem.h"



Application::Application()
:Application("default", 800,600)
{

}

Application::Application(const char *_title, int _width, int _height)
:m_title{_title}, m_width{_width}, m_height{_height}, m_window{nullptr}//, //m_camera{nullptr}
{

    //window inits glfw, maybe will add glad as well
    m_window = std::make_unique<FROST_RENDERING::Window>(m_title, m_width, m_height);
    if(!m_window)
    {
        printf("Failed to create windown\n");
    }

    glfwMakeContextCurrent(m_window->Handle());
    if(!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)))
    {
        printf("Failed to load glad\n");
    }

    //m_ecs = FrostEngine::ECS::Get();
    //m_camera = std::make_shared<FrostEngine::Camera2D>(m_width, m_height);
    m_mainContext.Register(FrostEngine::Camera2D{});

    m_isRunning = true;

    
}

Application::~Application()
{
    //TODO
    //glfw window ecs and so on
    printf("close\n");
}


void Application::Run()
{
    Init();
    while(m_isRunning && !glfwWindowShouldClose(m_window->Handle()))
    {
        m_window->PollEvents();
        Input();
        Update();
        Render();
        m_window->SwapBuffers();
    }
    Clean();
}