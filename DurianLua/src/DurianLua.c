#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include <stdio.h>

static int lua_Hello(lua_State* L)
{
	printf("Hello!\n");
	return 0;
}

static const luaL_Reg lib_Durian[] =
{
	{"Hello", lua_Hello},
	{NULL, NULL}
};

int luaopen_Durian(lua_State* L)
{
	luaL_newlib(L, lib_Durian);
	return 1;
}