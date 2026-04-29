#include "DamageSystem.h"


void DamageSystem::Update()
{
    for(auto &pair : m_ecs.GetEvents())
    {
        auto &e1 = pair.triggered;
        auto &e2 = pair.trigger;
        if(m_ecs.GetType(e1) == FrostEngine::EntityManager::Type::PLAYER &&
        m_ecs.GetType(e2) == FrostEngine::EntityManager::Type::ENEMY)
        {
           // std::cout<< "Entity " << e1 << "got fucked by Entity " << e2 << std::endl;
        }
    }
}