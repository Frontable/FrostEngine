#pragma once
#include <ECS/SystemManager.h>
#include <functional>
#include "FrostMath.h"
#include "ECS/Components.h"

class DamageSystem : public ISystem
{
public:
    DamageSystem(Context& _context) : ISystem{ _context } {}
    void Update(float dt) override;

    std::function<void()> OnGameOver;
    std::function<void(vec2 position, AsteroidTag::Size size, vec2 velocity)> OnAsteroidDestroyed;
};