#include <lua.hpp>
#include <stdio.h>

#include "Log.h"
#include "Entity.h"
#include "Tag.h"
#include "Transform.h"

extern "C"
{
	static const luaL_Reg lib_Durian[] =
	{
		// Logging
		{ "LogInfo", LogInfo },
        { "LogWarn", LogWarn },
        { "LogError", LogError },

		// Entity
		{"GetID", GetID},
		{"GetEntityByName", GetEntityByName},

		// Tag
		{"HasTag", HasTag},
		{"AttachTag", AttachTag},
		{"GetTag", GetTag},

		// Transform
		{"HasTransform", HasTransform},
		{"AttachTransform", AttachTransform},
		{"GetTransform", GetTransform},

		{NULL, NULL}
	};

	int luaopen_Durian(lua_State* L)
	{
		luaL_newlib(L, lib_Durian);
		return 1;
	}
}