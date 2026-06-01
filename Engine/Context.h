#pragma once
#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <functional>

struct Data
{
    Data() {}
    Data(void *d, std::function<void(void *)> f) : data(d), deleter(f) {}
    void *data;
    std::function<void(void *)> deleter;
};

class Context
{
public:
    template <typename T, typename... Args>
    void Add(Args &&...args)
    {
        m_DataMap.emplace(typeid(T), Data{ new T{std::forward<Args>(args)...}, [](void* ptr){
        delete static_cast<T *>(ptr); }});
    }    

    template <typename T>
    T &Get()
    {
        std::type_index type = typeid(T);
        auto it = m_DataMap.find(type);
        if (it != m_DataMap.end())
        {
            return *static_cast<T *>(m_DataMap[type].data);
        }
        throw std::runtime_error(std::string("[Context] Type not registered: ") + typeid(T).name());
    }

private:
    std::unordered_map<std::type_index, Data> m_DataMap;
};