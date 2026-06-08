#pragma once
#include <ECS/SystemManager.h>

class SpawnImmunitySystem : public ISystem
{
public:
    SpawnImmunitySystem(Context& _context) : ISystem{ _context } {}
    void Update(float dt) override;
};