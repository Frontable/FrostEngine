#include "Application.h"
#include "Core/Logger.h"
#include "Core/Time.h"
#include "Platform/Window.h"
#include "Renderer/OpenGLContext.h"
#include "Renderer/Renderer.h"
#include "Renderer/RendererPrimitives.h"
#include "Resources/ResourceManager.h"
#include "Math/Math.h"
#include "Renderer/VertexArray.h"
#include "glad/glad.h"

const char *vShader = R"(
#version 330 core
layout (location = 0) in vec2 vPos;
layout (location = 1) in vec2 vUV;
layout (location = 2) in vec3 vColor;

out vec3 color;

uniform mat4 uProjection;
uniform mat4 uModel;

void main()
{   
    color = vColor;
    gl_Position = uProjection * uModel * vec4(vPos, 0.0, 1.0);
}
)";

const char *fShader = R"(
#version 330 core

in vec3 color;

out vec4 FragColor;

void main()
{
    FragColor = vec4(color, 1.0);
    //FragColor = vec4(1.0, 0.25, 0.35, 1.0);
}
)";

namespace FrostEngine
{
    Application::Application(const AppSpec &spec)
    {
        m_spec = spec;
    }

    void Run(Application &app)
    {
        FROST_INIT_LOG(1, 1);
        Window window;
        window.Create(app.GetSpec().width, app.GetSpec().height, app.GetSpec().name);
        window.SetVSync(app.GetSpec().vsync);
        OpenGLContext::Init(window); // Initialize GLAD should be before all other
        Renderer::Init();           // Start renderer
        RendererPrimitives::Init(); // Generate VAO's and VBO's     
        ResourceManager::AddShaderFromSource("test", vShader, fShader);

        app.Init(); // Should come last to initialize

        constexpr double fixedDt = 1 / 60.0;
        double accumulator = 0.0;
        double last = Time::NowSeconds();

        while (window.IsOpen())
        {
            window.PollEvents();
            for (const auto &e : window.Events().Events())
            {
                app.OnEvent(e);
            }

            double now = Time::NowSeconds();
            double frame = now - last;
            last = now;
            if (frame > 0.25)
                frame = 0.25;

            accumulator += frame;

            glViewport(0, 0, window.Width(), window.Height());

            while (accumulator >= fixedDt)
            {
                app.Update(fixedDt);
                accumulator -= fixedDt;
            }

            double alpha = accumulator / fixedDt;
            
            Renderer::DrawQuad(vec2(100,100), vec2(100,100));
            app.Render(alpha);
            window.SwapBuffers();
        }

        app.Shutdown();
    }

    const AppSpec &Application::GetSpec() const
    {
        return m_spec;
    }
}