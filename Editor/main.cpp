#include "Application.h"
#include "Core/Logger.h"
#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"
#include "Renderer/RendererPrimitives.h"
#include "glad/glad.h"





class Game : public FrostEngine::Application
{
public:
    FrostEngine::ArrayBuffer* vao = nullptr;
    FrostEngine::Shader shader;

    

    Game()
        : FrostEngine::Application({1280, 720, "Game", true})
    {
    }

    void Init() override
    {
        FROST_LOG("Game OnInit()");
    }

    void Update(double dt) override
    {
        (void)dt;
    }

    void Render(double alpha) override
    {
        (void)alpha;    
        
        FrostEngine::Renderer::DrawQuad(vec2(500, 500), vec2(100,100));
    }

    void Shutdown() override
    {
        FROST_LOG("Game OnShutdown()");
    }
};

int main()
{
    Game game;
    FrostEngine::Run(game);
    return 0;
}