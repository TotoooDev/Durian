#pragma once
#include <Durian/Scene/Entity.h>
#include <lua.hpp>
#include <string>

namespace Durian
{
    class LuaScript
    {
    public:
        LuaScript(const std::string& path, Entity entity);
        ~LuaScript();

        std::string GetPath() { return m_Path; }
        bool HasStarted() { return m_HasStarted; }

        void SetPath(const std::string& path) { m_Path = path; }
        void Recompile();

        void OnStart();
        void OnUpdate(double timestep);
        void OnEnd();

    private:
        void Create();
        bool CheckLua(int r);

        lua_State* m_State = nullptr;
        Entity m_Ent;
        std::string m_Path;
        bool m_HasStarted;
    };
}