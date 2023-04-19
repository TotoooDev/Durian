#pragma once
#include <lua.hpp>
#include "Utils.h"
#include <Durian/Scene/Components.h>

extern "C"
{
    static int GetSprite(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& sprite = ent->GetComponent<Durian::SpriteComponent>();

        lua_createtable(L, 1, 7);
        {
            lua_pushboolean(L, sprite.Draw);
            lua_setfield(L, -2, "Draw");
        }

        return 1;
    }
}