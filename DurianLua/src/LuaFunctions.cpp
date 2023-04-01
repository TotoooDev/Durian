#include <lua.hpp>
#include <stdio.h>

static int HelloDurian(lua_State* L)
{
    printf("Hello Durian! (from Lua)\n");
    return 0;
}

static const struct luaL_Reg libDurian[] =
{
    { "HelloDurian", HelloDurian },
    { NULL, NULL }
};

int luaopen_libDurian(lua_State* L)
{
    luaL_newlib(L, libDurian);
    return 1;
}