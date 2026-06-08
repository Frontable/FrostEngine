#include "Application.h"
#include "glad/glad.h"
#include "Context.h"
#include "Logger/Logger.h"
#include "Input.h"
#include "ECS/ECS.h"
#include "Rendering/Essentials/ShaderLoader.h"
#include "Rendering/Essentials/TextureLoader.h"

Application::Application()
    : Application("default", 1280, 720)
{
}

Application::Application(const char* title, int width, int height)
    : m_Title(title), m_Width(width), m_Height(height)
{
    FROST_INIT_LOG(true, true);

    // Window — every game needs this
    m_MainContext.Add<FROST_RENDERING::Window>(m_Title, m_Width, m_Height);
    auto& window = m_MainContext.Get<FROST_RENDERING::Window>();

    glfwMakeContextCurrent(window.Handle());
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        FROST_ERROR("Failed to initialize GLAD");

    glViewport(0, 0, m_Width, m_Height);
}


void Application::Run()
{
    Init();
    double lastTime = glfwGetTime();
    auto& m_window = m_MainContext.Get<FROST_RENDERING::Window>();

    while (m_IsRunning && !glfwWindowShouldClose(m_window.Handle()))
    {
        double currentTime = glfwGetTime();
        float dt = (float)(currentTime - lastTime);
        lastTime = currentTime;  // ← this is the missing line

        // Clamp dt to avoid spiral of death when paused/debugging
        if (dt > 0.05f) dt = 0.05f;

        Input::Update();
        m_window.PollEvents();
        Input(dt);
        Update(dt);

        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Render(dt);
        m_window.SwapBuffers();
    }

    Clean();
}