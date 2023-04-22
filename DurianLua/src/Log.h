#pragma once
#include <lua.hpp>

#include <Durian/Core/Log.h>

// TODO: Put the spdlog sink thing to log in Durio
static int LogInfo(lua_State* L)
{
    if (lua_gettop(L) < 1)
        return 0;

    switch (lua_type(L, 1))
    {
    case LUA_TNUMBER:
        DURIAN_LOG_INFO(lua_tonumber(L, 1));
        break;
    case LUA_TSTRING:
        DURIAN_LOG_INFO(lua_tostring(L, 1));
        break;
    case LUA_TBOOLEAN:
        DURIAN_LOG_INFO(lua_toboolean(L, 1) ? "true" : "false");
        break;
    case LUA_TNIL:
        DURIAN_LOG_INFO("nil");
        break;
    default:
        DURIAN_LOG_INFO("{}", lua_topointer(L, 1));
        break;
    }
    return 0;
}
static int LogWarn(lua_State* L)
{
    if (lua_gettop(L) < 1)
        return 0;

    switch (lua_type(L, 1))
    {
    case LUA_TNUMBER:
        DURIAN_LOG_WARN(lua_tonumber(L, 1));
        break;
    case LUA_TSTRING:
        DURIAN_LOG_WARN(lua_tostring(L, 1));
        break;
    case LUA_TBOOLEAN:
        DURIAN_LOG_WARN(lua_toboolean(L, 1) ? "true" : "false");
        break;
    case LUA_TNIL:
        DURIAN_LOG_WARN("nil");
        break;
    default:
        DURIAN_LOG_WARN("{}", lua_topointer(L, 1));
        break;
    }
    return 0;
}
static int LogError(lua_State* L)
{
    if (lua_gettop(L) < 1)
        return 0;

    switch (lua_type(L, 1))
    {
    case LUA_TNUMBER:
        DURIAN_LOG_ERROR(lua_tonumber(L, 1));
        break;
    case LUA_TSTRING:
        DURIAN_LOG_ERROR(lua_tostring(L, 1));
        break;
    case LUA_TBOOLEAN:
        DURIAN_LOG_ERROR(lua_toboolean(L, 1) ? "true" : "false");
        break;
    case LUA_TNIL:
        DURIAN_LOG_ERROR("nil");
        break;
    default:
        DURIAN_LOG_ERROR("{}", lua_topointer(L, 1));
        break;
    }
    return 0;
}