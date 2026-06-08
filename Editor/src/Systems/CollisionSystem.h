#pragma once
#include <ECS/SystemManager.h>

class CollisionSystem : public ISystem
{
public:
    CollisionSystem(Context& _context) : ISystem{ _context } {}
    void Update(float dt) override;
};