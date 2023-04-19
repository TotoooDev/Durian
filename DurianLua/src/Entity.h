#pragma once
#include <lua.hpp>
#include "Utils.h"
#include <Durian/Scene/Entity.h>
#include <Durian/Scene/Scene.h>
#include <Durian/Scene/Components.h>

extern "C"
{
    static int GetID(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        lua_pushnumber(L, (unsigned int)ent->GetID());
        return 1;
    }

    static int GetEntityByName(lua_State* L)
    {
        if (!lua_isstring(L, 1))
        {
            luaL_error(L, "GetEntityByName: excpected a string as argument 1");
            return 0;
        }

        std::string str = lua_tostring(L, 1);
        Durian::Entity* ent = GetEntity(L);
        entt::registry* reg = ent->GetParentScene()->GetRegistry();
        auto view = reg->view<Durian::TagComponent>();
        for (auto&& [id, tag] : view.each())
        {
            if (tag.Tag == str)
            {
                lua_pushnumber(L, (unsigned int)id);
                return 1;
            }
        }

        return 0;
    }
}