#pragma once
#include "Utils.h"
#include <lua.hpp>
#include <Durian/Scene/Entity.h>
#include <Durian/Scene/Components.h>

extern "C"
{
    // TODO: Remove this ctrl+c/ctrl+v monster and implement a metatable thing to watch the variable change
    // Warning! Boring copy-paste stuff
    // Preprocessor if to hide this boring ahh section of code
#if 1
    // == TRANSLATION ==
    // Set translation
    static int SetTranslationX(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Translation.x = lua_tonumber(L, 1);
        return 0;
    }
    static int SetTranslationY(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Translation.y = lua_tonumber(L, 1);
        return 0;
    }
    static int SetTranslationZ(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Translation.z = lua_tonumber(L, 1);
        return 0;
    }
    // Change translation
    static int ChangeTranslationX(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Translation.x += lua_tonumber(L, 1);
        return 0;
    }
    static int ChangeTranslationY(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Translation.y += lua_tonumber(L, 1);
        return 0;
    }
    static int ChangeTranslationZ(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Translation.z += lua_tonumber(L, 1);
        return 0;
    }
    // == ROTATION ==
    // Set rotation
    static int SetRotationX(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Rotation.x = lua_tonumber(L, 1);
        return 0;
    }
    static int SetRotationY(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Rotation.y = lua_tonumber(L, 1);
        return 0;
    }
    static int SetRotationZ(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Rotation.z = lua_tonumber(L, 1);
        return 0;
    }
    // Change rotation
    static int ChangeRotationX(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Rotation.x += lua_tonumber(L, 1);
        return 0;
    }
    static int ChangeRotationY(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Rotation.y += lua_tonumber(L, 1);
        return 0;
    }
    static int ChangeRotationZ(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Rotation.z += lua_tonumber(L, 1);
        return 0;
    }
    // == SCALE ==
    // Set scale
    static int SetScaleX(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Scale.x = lua_tonumber(L, 1);
        return 0;
    }
    static int SetScaleY(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Scale.y = lua_tonumber(L, 1);
        return 0;
    }
    static int SetScaleZ(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Scale.z = lua_tonumber(L, 1);
        return 0;
    }
    // Change rotation
    static int ChangeScaleX(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Scale.x += lua_tonumber(L, 1);
        return 0;
    }
    static int ChangeScaleY(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Scale.y += lua_tonumber(L, 1);
        return 0;
    }
    static int ChangeScaleZ(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();
        if (lua_isnumber(L, 1))
            transform.Scale.z += lua_tonumber(L, 1);
        return 0;
    }
#endif

    static int HasTransform(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        lua_pushboolean(L, ent->HasComponent<Durian::TransformComponent>());
        return 1;
    }

    static int GetTransform(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->GetComponent<Durian::TransformComponent>();

        lua_createtable(L, 3, 0);
        {
            lua_createtable(L, 0, 3);
            {
                lua_pushnumber(L, transform.Translation.x);
                lua_setfield(L, -2, "x");
                lua_pushnumber(L, transform.Translation.y);
                lua_setfield(L, -2, "y");
                lua_pushnumber(L, transform.Translation.z);
                lua_setfield(L, -2, "z");

                lua_pushcfunction(L, SetTranslationX);
                lua_setfield(L, -2, "SetX");
                lua_pushcfunction(L, SetTranslationY);
                lua_setfield(L, -2, "SetY");
                lua_pushcfunction(L, SetTranslationZ);
                lua_setfield(L, -2, "SetZ");

                lua_pushcfunction(L, ChangeTranslationX);
                lua_setfield(L, -2, "ChangeX");
                lua_pushcfunction(L, ChangeTranslationY);
                lua_setfield(L, -2, "ChangeY");
                lua_pushcfunction(L, ChangeTranslationZ);
                lua_setfield(L, -2, "ChangeZ");

                lua_setfield(L, -2, "Translation");
            }
            lua_createtable(L, 0, 3);
            {
                lua_pushnumber(L, transform.Rotation.x);
                lua_setfield(L, -2, "x");
                lua_pushnumber(L, transform.Rotation.y);
                lua_setfield(L, -2, "y");
                lua_pushnumber(L, transform.Rotation.z);
                lua_setfield(L, -2, "z");

                lua_pushcfunction(L, SetRotationX);
                lua_setfield(L, -2, "SetX");
                lua_pushcfunction(L, SetRotationY);
                lua_setfield(L, -2, "SetY");
                lua_pushcfunction(L, SetRotationZ);
                lua_setfield(L, -2, "SetZ");

                lua_pushcfunction(L, ChangeRotationX);
                lua_setfield(L, -2, "ChangeX");
                lua_pushcfunction(L, ChangeRotationY);
                lua_setfield(L, -2, "ChangeY");
                lua_pushcfunction(L, ChangeRotationZ);
                lua_setfield(L, -2, "ChangeZ");

                lua_setfield(L, -2, "Rotation");
            }
            lua_createtable(L, 0, 3);
            {
                lua_pushnumber(L, transform.Scale.x);
                lua_setfield(L, -2, "x");
                lua_pushnumber(L, transform.Scale.y);
                lua_setfield(L, -2, "y");
                lua_pushnumber(L, transform.Scale.z);
                lua_setfield(L, -2, "z");

                lua_pushcfunction(L, SetScaleX);
                lua_setfield(L, -2, "SetX");
                lua_pushcfunction(L, SetScaleY);
                lua_setfield(L, -2, "SetY");
                lua_pushcfunction(L, SetScaleZ);
                lua_setfield(L, -2, "SetZ");

                lua_pushcfunction(L, ChangeScaleX);
                lua_setfield(L, -2, "ChangeX");
                lua_pushcfunction(L, ChangeScaleY);
                lua_setfield(L, -2, "ChangeY");
                lua_pushcfunction(L, ChangeScaleZ);
                lua_setfield(L, -2, "ChangeZ");

                lua_setfield(L, -2, "Scale");
            }
        }

        return 1;
    }

    static int AttachTransform(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        auto& transform = ent->AddComponent<Durian::TransformComponent>();
        return GetTransform(L);
    }
}