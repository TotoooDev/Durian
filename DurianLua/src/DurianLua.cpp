#include <lua.hpp>
#include <stdio.h>

#include "Log.h"
#include "Entity.h"

extern "C"
{
	static const luaL_Reg lib_Durian[] =
	{
		// Logging
		{ "LogInfo", LogInfo },
        { "LogWarn", LogWarn },
        { "LogError", LogError },

		// Entity
		{"GetID", Entity_GetID},

		{NULL, NULL}
	};

	int luaopen_Durian(lua_State* L)
	{
		luaL_newlib(L, lib_Durian);
		return 1;
	}
}