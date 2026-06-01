#pragma once
#include <ECS/SystemManager.h>

class LifetimeSystem : public ISystem
{
    public:
    LifetimeSystem(Context &_context) : ISystem{_context} {}

    void Update(float dt) override;

    void SetPlayer(Entity &_player) { player = &_player; }

    Entity *player;
};