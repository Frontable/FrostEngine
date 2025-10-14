

#pragma once
#include "EntityManager.h"
#include <typeinfo>
#include <memory>
#include "glm/glm.hpp"

struct Fuck
{
};

struct Transform
{   
    Transform()
    : position(0), size(0), rotation(0)
    {

    }

    Transform(glm::vec2 pos, glm::vec2 size, float rotation)
        : position(pos), size(size), rotation(rotation)
    {
    }
    glm::vec2 position;
    glm::vec2 size;
    float rotation;
};

class IComponentArray
{

public:
    virtual void EntityDestroyed() = 0;
};

template <class T>
class ComponentArray : public IComponentArray
{

public:
    std::unordered_map<Entity, T> m_componentArray;

    void EntityDestroyed() override
    {
    }

    void AddComponent(Entity entity, T component)
    {
        m_componentArray.emplace(entity, component);
    }

    T& GetComponent(Entity entity)
    {
        return m_componentArray[entity];
    }

};

class ComponentManager
{

public:
    int nextID = 0;
    std::unordered_map<size_t, std::unique_ptr<IComponentArray>> m_componentArrays;
    std::unordered_map<int, size_t> m_componentID;
    

    static ComponentManager* getInstance()
    {
        if(m_componentManager == nullptr)
        {
            m_componentManager = new ComponentManager();
        }

        return m_componentManager;

    }


    template <class T>
    void RegisterComponent()
    {
        size_t hash = typeid(T).hash_code();
        auto it = m_componentArrays.find(hash);
        if (it != m_componentArrays.end())
        {
            printf("Component has already beed registered\n");
            return;
        }

        m_componentID.emplace(nextID++, hash);
        m_componentArrays.emplace(hash, std::make_unique<ComponentArray<T>>());
        //std::cout << "Component: " << typeid(T).name() << std::endl;
        //std::cout << "Component type is: " << typeid(T).hash_code() << std::endl;
        //printf("Registered component: %zu\n", hash);
    }

    template <class T>
    void AddComponent(Entity entity, T component)
    {
        if (!CheckComponent<T>())
            return;

        GetComponentArray<T>()->AddComponent(entity, component);
        std::cout << "Added component ID: " << typeid(T).hash_code() << " component: " << typeid(T).name() << " to entity : " << entity << std::endl;
    }

    template<class T>
    T& getComponent(Entity entity)
    {
        return GetComponentArray<T>()->GetComponent(entity);
    }


private:
    template <class T>
    ComponentArray<T> *GetComponentArray()
    {
        size_t hash = typeid(T).hash_code();
        return static_cast<ComponentArray<T> *>(m_componentArrays[hash].get());
    }

    template <class T>
    bool CheckComponent()
    {
        size_t hash = typeid(T).hash_code();
        auto it = m_componentArrays.find(hash);
        if (it == m_componentArrays.end())
        {
            printf("Component has not been registered\n");
            return false;
        }
        return true;
    }
    static ComponentManager* m_componentManager;
    ComponentManager(){};
    ComponentManager(const ComponentManager&) = delete;

};
