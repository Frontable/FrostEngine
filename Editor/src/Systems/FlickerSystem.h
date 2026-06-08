#pragma once
#include <ECS/SystemManager.h>

class FlickerSystem : public ISystem
{
public:
    FlickerSystem(Context& _context) : ISystem{ _context } {}
    void Update(float dt) override;
};