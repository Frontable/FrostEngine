#pragma once
#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <functional>
#include "Logger/Logger.h"

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
    T& Get()
    {
        auto it = m_DataMap.find(typeid(T));

        if (it != m_DataMap.end())
        {
            return *static_cast<T*>(it->second.data);
        }

        //throw ...
    }

    ~Context() {
        for (auto& [key, val] : m_DataMap)
            val.deleter(val.data);
    }

private:
    std::unordered_map<std::type_index, Data> m_DataMap;
};