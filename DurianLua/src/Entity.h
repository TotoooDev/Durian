#include <lua.hpp>
#include <Durian/Scene/Entity.h>
#include <Durian/Scene/Components.h>

extern "C"
{
    static int Entity_GetID(lua_State* L)
    {
        lua_getglobal(L, "DurianEntity");
        Durian::Entity* ent = (Durian::Entity*)lua_touserdata(L, -1);
        lua_pushnumber(L, (unsigned int)ent->GetID());
        return 1;
    }
}