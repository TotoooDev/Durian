#include <pch.h>
#include <Durian/Scene/Script.h>
#include <Durian/Scene/Entity.h>

namespace Durian
{
    LuaScript::LuaScript(const std::string& path, Entity entity)
        : m_Path(path), m_Ent(entity)
    {
        if (!path.empty())
            Create();
    }

    LuaScript::~LuaScript()
    {
        // OnEnd();
        // if (m_State != nullptr)
        //     lua_close(m_State);
    }

    void LuaScript::Recompile()
    {
        m_HasStarted = false;
        if (m_State != nullptr)
            lua_close(m_State);
        Create();
    }

    void LuaScript::OnStart()
    {
        lua_getglobal(m_State, "OnStart");
        if (lua_isfunction(m_State, -1))
            CheckLua(lua_pcall(m_State, 0, 0, 0));
        m_HasStarted = true;
    }

    void LuaScript::OnUpdate(double timestep)
    {
        lua_getglobal(m_State, "OnUpdate");
        if (lua_isfunction(m_State, -1))
        {
            lua_pushnumber(m_State, timestep);
            CheckLua(lua_pcall(m_State, 1, 0, 0));
        }
    }

    void LuaScript::OnEnd()
    {
        lua_getglobal(m_State, "OnEnd");
        if (lua_isfunction(m_State, -1))
            CheckLua(lua_pcall(m_State, 0, 0, 0));
    }

    void LuaScript::Create()
    {
        m_State = luaL_newstate();
        luaL_openlibs(m_State);

        CheckLua(luaL_dofile(m_State, m_Path.c_str()));

        // Pass the entity as a global variable in the script
        lua_pushlightuserdata(m_State, &m_Ent);
        lua_setglobal(m_State, "DurianEntity");
    }

    bool LuaScript::CheckLua(int r)
    {
        if (r != LUA_OK)
        {
            DURIAN_LOG_ERROR(lua_tostring(m_State, -1));
            return false;
        }

        return true;
    }
}