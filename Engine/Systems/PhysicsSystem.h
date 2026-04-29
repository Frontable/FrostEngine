#pragma once
#include "ECS/ECS.h"
#include "Window.h"

class PhysicsSystem : public ISystem
{
    public:
    
    FrostEngine::ECS &m_ecs = FrostEngine::ECS::get();
    FROST_RENDERING::Window *m_window{nullptr};
    void Update() override;

};