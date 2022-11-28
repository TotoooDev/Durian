#pragma once
#include <Durian/Scene/Entity.h>
#include <Durian/Event/Events.h>
extern "C"
{
    #include "Lua/lua.h"
    #include "Lua/lauxlib.h"
    #include "Lua/lualib.h"
}
#include <string>

namespace Durian
{
    struct TransformComponent;

    class LuaScript
    {
    public:
        LuaScript(Entity ent, const std::string& filePath = "");
        
        void OnStart();
        void OnUpdate(float timestep);

        void GetTransformComponent(TransformComponent* comp);

    private:
        bool CheckLua(int r);

        lua_State* m_State;
        std::string m_Path;

        struct UserData
        {
            Entity Ent;
            int KeyDown = 0;
            int KeyUp = 0;
        } m_UserData;

        void OnKeyDown(KeyDownEvent* event);
        void OnKeyUp(KeyUpEvent* event);
    };
}