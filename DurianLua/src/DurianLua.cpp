#include <lua.hpp>
#include <stdio.h>

#include "Log.h"
#include "Entity.h"
#include "Tag.h"

extern "C"
{
	static const luaL_Reg lib_Durian[] =
	{
		// Logging
		{ "LogInfo", LogInfo },
        { "LogWarn", LogWarn },
        { "LogError", LogError },

		// Entity
		{ "GetID", GetID },
		{ "GetEntityByName", GetEntityByName },

		// Tag
		{ "GetTag", TagGet },
		{ "AttachTag", TagAttach },
		{ "DetachTag", TagDetach },

		{NULL, NULL}
	};

	int luaopen_Durian(lua_State* L)
	{
		RegisterTag(L);
		luaL_newlib(L, lib_Durian);
		return 1;
	}
}