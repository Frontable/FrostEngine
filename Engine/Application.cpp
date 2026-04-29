#include "Application.h"
#include "glad/glad.h"
#include "Context.h"
#include "Systems/RenderingSystem.h"
#include "Logger/Logger.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/DamageSystem.h"
#include "Input.h"



Application::Application()
:Application("default", 800,600)
{
    
}

Application::Application(const char *_title, int _width, int _height)
:m_title{_title}, m_width{_width}, m_height{_height}, m_window{nullptr}//, //m_camera{nullptr}
{
    
    FROST_INIT_LOG(true, true);
    //window inits glfw, maybe will add glad as well
    m_window = std::make_unique<FROST_RENDERING::Window>(m_title, m_width, m_height);

    glfwMakeContextCurrent(m_window->Handle());
    if(!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)))
    {
        FROST_ERROR("Failed to initialize GLAD");
    }
    glViewport(0, 0, m_width, m_height);
    //m_ecs = FrostEngine::ECS::Get();
    //m_camera = std::make_shared<FrostEngine::Camera2D>(m_width, m_height);
    m_mainContext.Register(FrostEngine::Camera2D{});

    m_ecs.RegisterSystem<PhysicsSystem>();
    auto &phys = m_ecs.getSystem<PhysicsSystem>();
    Signature physSig{};
    physSig.set(m_ecs.GetComponentID<Transform2D>());
    m_ecs.SetSystemSignature<PhysicsSystem>(physSig);

    m_ecs.RegisterSystem<CollisionSystem>();
    Signature colSig{};
    colSig.set(m_ecs.GetComponentID<Transform2D>());
    colSig.set(m_ecs.GetComponentID<BoxCollider>());
    m_ecs.SetSystemSignature<CollisionSystem>(colSig);

    m_ecs.RegisterSystem<RenderingSystem>();
    auto &renderer = m_ecs.getSystem<RenderingSystem>();
    renderer.init();
    Signature renderSyg{};
    renderSyg.set(m_ecs.GetComponentID<Transform2D>());
    //renderSyg.set(m_ecs.GetComponentID<Sprite>());
    m_ecs.SetSystemSignature<RenderingSystem>(renderSyg);

    m_ecs.RegisterSystem<DamageSystem>();


    m_isRunning = true;    
    //std::cout<<*phys.m_entities.begin();
}

Application::~Application()
{
    //TODO
    //glfw window ecs and so on
}


void Application::Run()
{
    Init();

    double lastTime = glfwGetTime();
    double timer = 0.0;
    int frames = 0;

    while (m_isRunning && !glfwWindowShouldClose(m_window->Handle()))
    {
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        timer += deltaTime;
        frames++;

        // Print every second
        if (timer >= 1.0)
        {
            double fps = frames / timer;
            double msPerFrame = (timer / frames) * 1000.0;

            std::cout << "FPS: " << fps 
                      << " | Frame Time: " << msPerFrame << " ms\n";

            frames = 0;
            timer = 0.0;
        }

        Input::Update();
        m_window->PollEvents();
        Input();

        Update();

        glClearColor(0.1, 0.2, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        Render();

        m_window->SwapBuffers();
    }

    Clean();
}