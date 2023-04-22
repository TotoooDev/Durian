#pragma once
#include <lua.hpp>
#include <Durian/Scene/Entity.h>
#include <Durian/Core/Log.h>

extern "C"
{
    Durian::Entity* GetEntity(lua_State* L)
    {
        lua_getglobal(L, "DurianEntity");
        Durian::Entity* ent = (Durian::Entity*)lua_touserdata(L, -1);
        lua_pop(L, 1);
        return ent;
    }

    void DumpStack(lua_State* L)
    {
        DURIAN_LOG_INFO("== DUMPING LUA STACK ==");
        int top = lua_gettop(L);
        for (int i = 1; i <= top; i++)
        {
            DURIAN_LOG_INFO("{0}: {1}", i, lua_typename(L, lua_type(L, i)));
            switch (lua_type(L, i))
            {
            case LUA_TNUMBER:
                DURIAN_LOG_INFO(lua_tonumber(L, i));
                break;
            case LUA_TSTRING:
                DURIAN_LOG_INFO(lua_tostring(L, i));
                break;
            case LUA_TBOOLEAN:
                DURIAN_LOG_INFO(lua_toboolean(L, i) ? "true" : "false");
                break;
            case LUA_TNIL:
                DURIAN_LOG_INFO("nil");
                break;
            default:
                DURIAN_LOG_INFO("{}", lua_topointer(L, i));
                break;
            }
        }
    }
}