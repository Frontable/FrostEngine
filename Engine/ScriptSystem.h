#pragma once
#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>
#include <iostream>
#include <set>
#include "ECS/ECS.h"
#include "ECS/Components.h"

struct ScriptComponent
{
    std::string tableName;
    sol::table instance{sol::lua_nil};
    bool initialized = false;

    ScriptComponent() = default;
    ScriptComponent(const std::string &_tableName)
        : tableName(_tableName) {}
};

class ScriptingSystem
{
public:
    ScriptingSystem(FrostEngine::ECS &_ecs)
        : m_ecs(_ecs)
    {
        m_lua.open_libraries(
            sol::lib::base,
            sol::lib::package,
            sol::lib::math,
            sol::lib::table,
            sol::lib::string);

        BindFunctions();
    }

    bool LoadScriptFile(const std::string &path)
    {
        sol::protected_function_result result = m_lua.safe_script_file(path);

        if (!result.valid())
        {
            sol::error err = result;
            std::cerr << "Error loading lua file: " << err.what() << std::endl;
            return false;
        }

        return true;
    }

    void AddEntity(Entity entity)
    {
        m_entities.insert(entity);
    }

    void InitScripts()
    {
        for (Entity e : m_entities)
        {
            auto &script = m_ecs.GetComponent<ScriptComponent>(e);

            std::cout << "Trying to init entity " << e
                      << " with table name: " << script.tableName << std::endl;

            if (script.initialized)
                continue;

            sol::object obj = m_lua[script.tableName];

            if (!obj.valid())
            {
                std::cout << "Lua object not found: " << script.tableName << std::endl;
                continue;
            }

            if (obj.get_type() != sol::type::table)
            {
                std::cout << script.tableName << " is not a table\n";
                continue;
            }

            script.instance = obj.as<sol::table>();
            script.instance["entity"] = e;

            std::cout << "Lua table found for entity " << e << std::endl;

            CallIfExists(script.instance, "onCreate");
            script.initialized = true;
        }
    }

    void Update(float dt)
{
    for (Entity e : m_entities)
    {
        auto& script = m_ecs.GetComponent<ScriptComponent>(e);

        //std::cout << "Update entity " << e
         //         << " initialized = " << script.initialized
          //        << " instance valid = " << script.instance.valid()
           //       << std::endl;

        if (!script.initialized || !script.instance.valid())
            continue;

        CallIfExists(script.instance, "onUpdate", dt);
    }
}

private:
    FrostEngine::ECS &m_ecs;
    sol::state m_lua;
    std::set<Entity> m_entities;

    void BindFunctions()
    {
        m_lua.set_function("set_position", [this](Entity e, float x, float y)
                           {
            auto& transform = m_ecs.GetComponent<Transform2D>(e);
            transform.position.x = x;
            transform.position.y = y; });

        m_lua.set_function("get_position_x", [this](Entity e) -> float
                           { return m_ecs.GetComponent<Transform2D>(e).position.x; });

        m_lua.set_function("get_position_y", [this](Entity e) -> float
                           { return m_ecs.GetComponent<Transform2D>(e).position.y; });

        m_lua.set_function("print_position", [this](Entity e)
                           {
            auto& transform = m_ecs.GetComponent<Transform2D>(e);
            std::cout << "Entity " << e
                      << " Position: (" << transform.position.x
                      << ", " << transform.position.y << ")\n"; });
    }

    void CallIfExists(sol::table &table, const std::string &fnName)
    {
        sol::object obj = table[fnName];
        if (!obj.valid() || obj.get_type() != sol::type::function)
            return;

        sol::protected_function fn = obj.as<sol::protected_function>();
        sol::protected_function_result result = fn(table);

        if (!result.valid())
        {
            sol::error err = result;
            std::cerr << "Lua error in " << fnName << ": "
                      << err.what() << std::endl;
        }
    }

    void CallIfExists(sol::table &table, const std::string &fnName, float dt)
    {
        sol::object obj = table[fnName];
        if (!obj.valid() || obj.get_type() != sol::type::function)
            return;

        sol::protected_function fn = obj.as<sol::protected_function>();
        sol::protected_function_result result = fn(table, dt);

        if (!result.valid())
        {
            sol::error err = result;
            std::cerr << "Lua error in " << fnName << ": "
                      << err.what() << std::endl;
        }
    }
};