#include "Application.h"
#include "glad/glad.h"
#include "Context.h"
#include "Systems/RenderingSystem.h"
#include "Logger/Logger.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/DamageSystem.h"
#include "Input.h"
#include "ECS/ECS.h"
#include "Rendering/Essentials/ShaderLoader.h"
#include "Rendering/Essentials/TextureLoader.h"

Application::Application()
    : Application("default", 800, 600)
{
}

Application::Application(const char *_title, int _width, int _height)
    : m_Title{_title}, m_Width{_width}, m_Height{_height}//, m_window{nullptr} //, //m_camera{nullptr}
{

    FROST_INIT_LOG(true, true);
    //window inits glfw, maybe will add glad as well
    m_MainContext.Add<FROST_RENDERING::Window>(m_Title, m_Width, m_Height);
    auto &m_window = m_MainContext.Get<FROST_RENDERING::Window>();
    //m_window = std::make_unique<FROST_RENDERING::Window>(m_title, m_width, m_height);

    glfwMakeContextCurrent(m_window.Handle());
    if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress)))
    {
        FROST_ERROR("Failed to initialize GLAD");
    }
    glViewport(0, 0, m_Width, m_Height);
    //m_ecs = FrostEngine::ECS::Get();
    //m_camera = std::make_shared<FrostEngine::Camera2D>(m_width, m_height);
    //--------------------------------
    //  CAMERA
    //-------------------------------
    m_MainContext.Add<FrostEngine::Camera2D>(800, 600);
    //--------------------------------
    // CAMERA
    //-------------------------------
    m_Renderer = new SpriteBatchRenderer{};
    m_Shader = FrostEngine::ShaderLoader::Create(
        "D:/Projects/FrostEngine/Engine/Assets/Shaders/basicV.glsl", 
        "D:/Projects/FrostEngine/Engine/Assets/Shaders/basicF.glsl");
    m_Texture = FrostEngine::TextureLoader::Create(
        FrostEngine::Texture::TextureType::BLENDED, 
        "D:/Projects/FrostEngine/data/images/asteroids.png");
    //--------------------------------
    // ECS SYSTEMS
    //-------------------------------
    //FrostEngine::ECS *ecs = new FrostEngine::ECS{};
    m_MainContext.Add<FrostEngine::ECS>();
    //ecs.CreateEntity();
    auto& m_ecs = m_MainContext.Get<FrostEngine::ECS>();
    
    //--------------------------------
    // ECS SYSTEMS
    //-------------------------------

    m_IsRunning = true;
    // std::cout<<*phys.m_entities.begin();
}

Application::~Application()
{
    // TODO
    // glfw window ecs and so on
}

void Application::Run()
{
    Init();

    double lastTime = glfwGetTime();
    double timer = 0.0;
    int frames = 0;
    auto &m_window = m_MainContext.Get<FROST_RENDERING::Window>();
    while (m_IsRunning && !glfwWindowShouldClose(m_window.Handle()))
    {
        
        float currentTime = (float)glfwGetTime();
        float dt = currentTime - lastTime;
        Input::Update();
        m_window.PollEvents();
        Input(dt);

        Update(dt);

        glClearColor(0.1, 0.2, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        Render(dt);

        m_window.SwapBuffers();
    }

    Clean();
}