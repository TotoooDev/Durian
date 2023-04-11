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

    }

    void LuaScript::OnUpdate(double timestep)
    {

    }

    void LuaScript::OnEnd()
    {

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