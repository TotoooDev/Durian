#pragma once
#include <lua.hpp>
#include <Durian/Scene/Components.h>
#include "Utils.h"

extern "C"
{
    Durian::TagComponent* CheckTag(lua_State* L)
    {
        Durian::TagComponent* tag = (Durian::TagComponent*)luaL_checkudata(L, 1, "Durian.Tag");
        luaL_argcheck(L, tag != nullptr, 1, "'Tag' expected");
        return tag;
    }

    static int TagAttach(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        Durian::TagComponent* tag = CheckTag(L);
        const char* name = luaL_checkstring(L, 1);
        *tag = ent->AddComponent<Durian::TagComponent>(name);
        return 0;
    }

    static int TagDetach(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        ent->RemoveComponent<Durian::TagComponent>();
        return 0;
    }

    static int TagGet(lua_State* L)
    {
        Durian::Entity* ent = GetEntity(L);
        Durian::TagComponent* tag = (Durian::TagComponent*)lua_newuserdata(L, sizeof(Durian::TagComponent));
        **(&tag) = Durian::TagComponent();

        luaL_getmetatable(L, "Durian.Tag");
        lua_setmetatable(L, -2);

        Durian::TagComponent comp = ent->GetComponent<Durian::TagComponent>();
        *tag = comp;
        return 1;
    }

    static int TagToString(lua_State* L)
    {
        Durian::TagComponent* tag = CheckTag(L);
        lua_pushfstring(L, "%s", tag->Tag.c_str());
        return 1;
    }

    static int TagNewIndex(lua_State* L)
    {
        Durian::TagComponent* tag = CheckTag(L);
        const char* index = luaL_checkstring(L, 2);
        const char* value = luaL_checkstring(L, 3);

        if (strcmp(index, "Tag") == 0)
            tag->Tag = value;
        else
            printf("bad argument, expedcted 'Tag' but got %s\n", index);

        return 0;
    }

    static const luaL_Reg libTag[] =
    {
        { "__tostring", TagToString },
        { "__newindex", TagNewIndex },
        { nullptr, nullptr }
    };

    void RegisterTag(lua_State* L)
    {
        luaL_newmetatable(L, "Durian.Tag");
        lua_pushstring(L, "__index");
        lua_pushvalue(L, -2);
        lua_settable(L, -3);
        luaL_setfuncs(L, libTag, 0);
    }
}