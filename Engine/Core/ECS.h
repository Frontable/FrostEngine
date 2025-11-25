







#pragma once
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

class ECS
{
public:
    EntityManager *entityManager;
    ComponentManager *componentManager;
    // TODO: ADD a system maanger;
    // SystemManager* systemManager;
    TestSystem sys;
    void add(Entity entity)
    {
        sys.addEntitiy(entity);
    }

    void Update(float dt)
    {
        sys.Update(dt);
    }


    static ECS* getInstance();
    ~ECS();
private:
    static ECS *ecs;
    ECS();
    ECS(const ECS &) = delete;
};
