#include <pch.h>
#include <Durian/Scene/Script.h>

namespace Durian
{
    LuaScript::LuaScript(const std::string& filePath)
        : m_Path(filePath)
    {
        m_State = luaL_newstate();
        luaL_openlibs(m_State);
        if (!CheckLua(luaL_dofile(m_State, m_Path.c_str())))
            return;
    }

    bool LuaScript::CheckLua(int r)
    {
        if (r != LUA_OK)
        {
            std::string error = lua_tostring(m_State, -1);
            DURIAN_LOG_ERROR("[LUA]: {}", error);
            return false;
        }
        return true;
    }
}