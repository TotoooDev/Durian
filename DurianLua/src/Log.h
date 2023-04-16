#pragma once
#include <lua.hpp>

#include <Durian/Core/Log.h>

// TODO: Put the spdlog sink thing to log in Durio
static int LogInfo(lua_State* L)
{
    DURIAN_LOG_INFO(lua_tostring(L, 1));
    return 0;
}
static int LogWarn(lua_State* L)
{
    DURIAN_LOG_WARN(lua_tostring(L, 1));
    return 0;
}
static int LogError(lua_State* L)
{
    DURIAN_LOG_ERROR(lua_tostring(L, 1));
    return 0;
}