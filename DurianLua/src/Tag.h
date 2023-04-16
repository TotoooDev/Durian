#pragma once
#include <lua.hpp>

extern "C"
{
    struct Tag
    {
        const char* Name;
    };

    static int GetTag(lua_State* L)
    {
        
        return 1;
    }
}