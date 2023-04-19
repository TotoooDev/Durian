#pragma once
#include <lua.hpp>
#include "Utils.h"
#include <Durian/Scene/Components.h>

extern "C"
{
    static int GetTag(lua_State* L);

    static int SetTag(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& tag = ent->GetComponent<Durian::TagComponent>();
        if (lua_isstring(L, 1))
            tag.Tag = lua_tostring(L, 1);
        return GetTag(L);
    }

    static int HasTag(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        lua_pushboolean(L, ent->HasComponent<Durian::TagComponent>());
        return 1;
    }

    static int GetTag(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& tag = ent->GetComponent<Durian::TagComponent>();

        if (lua_gettop(L) == 1)
        {
            if (lua_isnumber(L, 1))
            {
                unsigned int id = lua_tointeger(L, 1);
                Durian::Entity otherEnt((entt::entity)id, ent->GetParentScene());
                tag = otherEnt.GetComponent<Durian::TagComponent>();
            }
        }

        lua_createtable(L, 0, 2);
        {
            lua_pushstring(L, tag.Tag.c_str());
            lua_setfield(L, -2, "Tag");
            lua_pushcfunction(L, SetTag);
            lua_setfield(L, -2, "SetTag");
        }

        return 1;
    }

    static int AttachTag(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        if (lua_isstring(L, 1))
        {
            const char* tag = lua_tostring(L, 1);
            ent->AddComponent<Durian::TagComponent>(tag);
            return GetTag(L);
        }
        return 0;
    }
}