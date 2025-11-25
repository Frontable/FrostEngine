






#pragma once
#include <set>

#include "ECS.h"

class System
{
protected:
    std::set<Entity> m_entities;
};

class TestSystem : public System
{

    public:

    void addEntitiy(Entity entity)
    {
        m_entities.insert(entity);
    }

    void Update(float dt)
    {
        for (auto &ent : m_entities)
        {
            auto &transform = ComponentManager::getInstance()->getComponent<Transform>(ent);
            transform.position.x++;
            std::cout<<"Entity: " << ent << " has position x of " << transform.position.x << std::endl;
        }
    }
};
