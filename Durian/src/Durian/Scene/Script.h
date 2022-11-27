#pragma once
extern "C"
{
    #include "Lua/lua.h"
    #include "Lua/lauxlib.h"
    #include "Lua/lualib.h"
}
#include <string>

namespace Durian
{
    class LuaScript
    {
    public:
        LuaScript(const std::string& filePath = "");

    private:
        bool CheckLua(int r);

        lua_State* m_State;
        std::string m_Path;
    };
}