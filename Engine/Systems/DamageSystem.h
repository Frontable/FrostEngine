#pragma once
#include "ECS/ECS.h"

class DamageSystem : public ISystem
{
    public:
    FrostEngine::ECS &m_ecs = FrostEngine::ECS::get();
    void Update() override;
};