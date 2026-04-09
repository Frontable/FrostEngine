#pragma once
#include <any>
#include <typeindex>
#include <unordered_map>

class Context
{
public:

    Context() = default;
    ~Context() = default;
    template<typename T>
    void Register(T value)
    {
        items[std::type_index(typeid(T))] = std::move(value);
    }

    template<typename T>
    bool Has()
    {
        return items.find(std::type_index(typeid(T))) != items.end();
    }

    template<typename T>
    T& Get()
    {
        auto it = items.find(std::type_index(typeid(T)));
        if(it == items.end())
        {
            throw std::runtime_error("not registered context\n");
        }
        return std::any_cast<T&>(it->second);
    }

private:
    std::unordered_map<std::type_index, std::any> items;
};