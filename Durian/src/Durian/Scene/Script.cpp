#include <pch.h>
#include <Durian/Scene/Script.h>

namespace Durian
{
    LuaScript::LuaScript(const std::string& path)
        : m_Path(path)
    {
        m_State = luaL_newstate();
        luaL_openlibs(m_State);

        CheckLua(luaL_dofile(m_State, m_Path.c_str()));
    }

    void LuaScript::OnStart()
    {
        lua_getglobal(m_State, "OnStart");
        if (lua_isfunction(m_State, -1))
            CheckLua(lua_pcall(m_State, 0, 0, 0));
    }

    void LuaScript::OnUpdate(double timestep)
    {
        lua_getglobal(m_State, "OnUpdate");
        lua_pushnumber(m_State, timestep);
        if (lua_isfunction(m_State, -1))
            CheckLua(lua_pcall(m_State, 1, 0, 0));
    }

    void LuaScript::OnEnd()
    {
        lua_getglobal(m_State, "OnEnd");
        if (lua_isfunction(m_State, -1))
            CheckLua(lua_pcall(m_State, 0, 0, 0));
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