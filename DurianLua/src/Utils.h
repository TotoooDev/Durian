#pragma once
#include <lua.hpp>
#include <Durian/Scene/Entity.h>

extern "C"
{
    Durian::Entity* GetEntity(lua_State* L)
    {
        lua_getglobal(L, "DurianEntity");
        return (Durian::Entity*)lua_touserdata(L, -1);
    }
}