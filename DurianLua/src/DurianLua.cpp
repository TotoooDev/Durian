#include <Durian/Core/OS.h>
#include <lua.hpp>
#include <iostream>

#ifdef DURIAN_WINDOWS
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT
#endif

static int lua_Hello(lua_State* L)
{
	std::cout << "Hello!" << std::endl;
	return 0;
}

static const luaL_Reg lib_Durian[] =
{
	{"Hello", lua_Hello},
	{nullptr, nullptr}
};

DLL_EXPORT int luaopen_Durian(lua_State* L)
{
	luaL_newlib(L, lib_Durian);
	return 1;
}