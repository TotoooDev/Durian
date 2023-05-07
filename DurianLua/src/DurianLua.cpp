#include <lua.hpp>
#include <stdio.h>
#include <Durian/Core/OS.h>

#include "Log.h"
#include "Entity.h"
#include "Tag.h"
#include "Transform.h"

#ifdef DURIAN_WINDOWS
	#define DURIAN_DLL __declspec(dllexport)
#else
	#define DURIAN_DLL 
#endif

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

		// Transform
		{ "GetTransform", TransformGet },
		{ "AttachTransform", TransformAttach },
		{ "DetachTransform", TransformDetach },

		{ nullptr, nullptr }
	};
	
	DURIAN_DLL int luaopen_Durian(lua_State* L)
	{
		RegisterTag(L);
		RegisterTransform(L);
		luaL_newlib(L, lib_Durian);
		return 1;
	}
}