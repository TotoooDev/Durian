#pragma once
#include "Utils.h"
#include <lua.hpp>
#include <Durian/Scene/Entity.h>
#include <Durian/Scene/Components.h>

extern "C"
{
    struct Vec3
    {
        float x, y, z;
    };

    struct Transform
    {
        Vec3 Translation, Rotation, Scale;
    };

    static int HasTransform(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        lua_pushboolean(L, ent->HasComponent<Durian::TransformComponent>());
        return 1;
    }

    static int AttachTransform(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->AddComponent<Durian::TransformComponent>();

        // Translation only for now
        lua_newtable(L);
        lua_newtable(L);
        lua_pushnumber(L, transform.Translation.x);
        lua_rawseti(L, -2, 1);
        lua_pushnumber(L, transform.Translation.y);
        lua_rawseti(L, -2, 2);
        lua_rawseti(L, -2, 1);
        
        return 1;
    }

    static int GetTransform(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();

        // Translation only for now
        lua_newtable(L);
        lua_pushnumber(L, transform.Translation.x);
        lua_setfield(L, -2, "x");
        lua_pushnumber(L, transform.Translation.y);
        lua_setfield(L, -2, "y");
        lua_pushnumber(L, transform.Translation.z);
        lua_setfield(L, -2, "z");

        return 1;
    }
}