

#pragma once
#include <string>
#include <queue>
#include <algorithm>
#include <iostream>
#include <bitset>
#include <unordered_map>

using Entity = std::uint32_t;
// using MAXCOMPONENTS = std::uint32_t;
constexpr unsigned int MAXCOMPONENTS = 32;
using ComponentSignature = std::bitset<MAXCOMPONENTS>;

class EntityManager
{
public:
    Entity m_counter = 0;
    std::unordered_map<Entity, ComponentSignature> m_entities;
    std::queue<Entity> m_freeEntities;
    std::unordered_map<Entity, ComponentSignature>::iterator i;

    Entity CreateEntity()
    {
        Entity entity;

        if (m_freeEntities.empty())
        {
            entity = m_counter;
            m_counter++;
        }
        else
        {
            entity = m_freeEntities.front();
            m_freeEntities.pop();
        }
        m_entities.emplace(entity, ComponentSignature{});
        printf("Created entity with ID: %d\n", entity);
        return entity;
    }

    void DeleteEntity(Entity entity)
    {
        i = m_entities.find(entity);
        if (i != m_entities.end())
        {
            m_entities.erase(entity);
            m_freeEntities.push(entity);
            printf("Deleted entity with ID: %d\n", entity);
            return;
        }

        printf("Entity with ID: %d does not exist\n", entity);
    }
};