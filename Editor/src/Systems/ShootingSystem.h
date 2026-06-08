#pragma once
#include <ECS/SystemManager.h>

class ShootingSystem : public ISystem
{
    public:
    ShootingSystem(Context &_context) : ISystem{_context} {}

    void Update(float dt) override;

};