#pragma once
#include "Window.h"
#include "Rendering/Essentials/Shader.h"
#include "Rendering/Essentials/Texture.h"
#include <memory>
#include "ECS/ECS.h"
#include "Rendering/Core/Camera2D.h"
#include "Context.h"
#include "SpriteBatchRenderer.h"



class Application
{
public:
    Application();
    Application(const char *_title, int _width, int _height);
    virtual ~Application();

    void Run();

    virtual void Init() = 0;
    virtual void Input(float dt) = 0;
    virtual void Update(float dt) = 0;
    virtual void Render(float dt) = 0;
    virtual void Clean() = 0;

protected:
    bool m_IsRunning;
    const char *m_Title;
    int m_Width, m_Height;
    Context m_MainContext{};

    //for testing
    SpriteBatchRenderer* m_Renderer;
    std::shared_ptr<FrostEngine::Shader> m_Shader;
    std::shared_ptr<FrostEngine::Texture> m_Texture;
};