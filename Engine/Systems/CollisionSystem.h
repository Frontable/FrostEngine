


#include "ECS/ECS.h"


class CollisionSystem : public ISystem
{
    public:
    FrostEngine::ECS &m_ecs = FrostEngine::ECS::get();
    void Update() override;

    bool AABB(Entity _triggered, Entity _trigger);
};