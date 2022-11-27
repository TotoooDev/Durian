#pragma once
#include <Durian/Scene/Entity.h>
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
        LuaScript(Entity ent, const std::string& filePath = "");
        
        void OnStart();
        void OnUpdate(float timestep);

        float GetNumber(const std::string& name);

    private:
        bool CheckLua(int r);

        lua_State* m_State;
        std::string m_Path;
    };
}