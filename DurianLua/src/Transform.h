#pragma once
#include <lua.hpp>
#include <Durian/Scene/Components.h>
#include "Utils.h"

extern "C"
{
    Durian::TransformComponent* CheckTransform(lua_State* L)
    {
        Durian::TransformComponent* transform = (Durian::TransformComponent*)luaL_checkudata(L, 1, "Durian.Transform");
        luaL_argcheck(L, transform != nullptr, 1, "'Transform' expected");
        return transform;
    }

    static int TransformAttach(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        ent->AddComponent<Durian::TransformComponent>();
        return 0;
    }

    static int TransformDetach(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        ent->RemoveComponent<Durian::TransformComponent>();
        return 0;
    }

    static int TransformGet(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        Durian::TransformComponent* transform = (Durian::TransformComponent*)lua_newuserdata(L, sizeof(Durian::TransformComponent));
        new(transform) Durian::TransformComponent();

        luaL_getmetatable(L, "Durian.Transform");
        lua_setmetatable(L, -2);

        Durian::TransformComponent comp = ent->GetComponent<Durian::TransformComponent>();
        *transform = comp;
        return 1;
    }

    static int TransformToString(lua_State* L)
    {
        Durian::TransformComponent* transform = CheckTransform(L);
        glm::vec3 translation = transform->Translation;
        glm::vec3 rotation = transform->Rotation;
        glm::vec3 scale = transform->Scale;
        // Ugly but easier to write
        lua_pushfstring(L,
R"({
    Translation: {
        x: %f,
        y: %f,
        z: %f
    },
    Rotation: {
        x: %f,
        y: %f,
        z: %f
    },
    Scale: {
        x: %f,
        y: %f,
        z: %f
    }
})", 
        translation.x, translation.y, translation.z, rotation.x, rotation.y, rotation.z, scale.x, scale.y, scale.z);
        return 1;
    }

    static int TransformNewIndex(lua_State* L)
    {
        Durian::TagComponent* tag = CheckTag(L);
        const char* index = luaL_checkstring(L, 2);
        const char* value = luaL_checkstring(L, 3);
        return 0;
    }

    static const luaL_Reg libTransform[] =
    {
        { "__tostring", TransformToString },
        { "__newindex", TransformNewIndex },
        { nullptr, nullptr }
    };

    void RegisterTransform(lua_State* L)
    {
        luaL_newmetatable(L, "Durian.Transform");
        lua_pushstring(L, "__index");
        lua_pushvalue(L, -2);
        lua_settable(L, -3);
        luaL_setfuncs(L, libTransform, 0);
    }
}