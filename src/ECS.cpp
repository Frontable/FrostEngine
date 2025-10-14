






#include "ECS.h"

ComponentManager* ComponentManager::m_componentManager = nullptr;
ECS* ECS::ecs = nullptr;

ECS::ECS()
{
    entityManager = new EntityManager();
    componentManager = ComponentManager::getInstance();
}

ECS::~ECS()
{
    delete entityManager;
    delete componentManager;
}

ECS *ECS::getInstance()
{
    if (ecs == nullptr)
    {
        ecs = new ECS();
    }
    return ecs;
}