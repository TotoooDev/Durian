#pragma once
#include <lua.hpp>
#include "Utils.h"
#include <Durian/Scene/Entity.h>
#include <Durian/Scene/Components.h>

extern "C"
{
    static int Entity_GetID(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        lua_pushnumber(L, (unsigned int)ent->GetID());
        return 1;
    }
}