#pragma once
#include "ECS/ECS.h"
#include "SpriteBatchRenderer.h"
#include "Rendering/Essentials/TextureLoader.h"
#include "Rendering/Essentials/ShaderLoader.h"
#include "Rendering/Core/Camera2D.h"

class RenderingSystem : public ISystem
{
    public:
    GLuint VAO, VBO;
    std::shared_ptr<FrostEngine::Texture> tex;
    std::shared_ptr<FrostEngine::Shader> shader;
    FrostEngine::Camera2D* cam = nullptr;
    SpriteBatchRenderer* renderer{nullptr};
    FrostEngine::ECS &m_ecs = FrostEngine::ECS::get();
    void init();
    void Update() override;

};