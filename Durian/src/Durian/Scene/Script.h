#pragma once
#include <Durian/Scene/Entity.h>
#include <Durian/Event/Events.h>
#include <Durian/Audio/SoundPool.h>
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
        ~LuaScript();
        
        void OnStart();
        void OnUpdate(float timestep);

        void Recompile();

        void GetTransformComponent(TransformComponent* comp);

    private:
        void Create();
        void SetCppFunctions();
        bool CheckLua(int r);

        lua_State* m_State;
        std::string m_Path;

        struct UserData
        {
            Entity Ent;
            SoundPool* Sounds;

            int KeyDown = 0, KeyUp = 0;

            int MouseX = 0, MouseY = 0;
            int ButtonDown = 0, ButtonUp = 0;
            float ScrollX = 0.0f, ScrollY = 0.0f;

            int WindowX = 0, WindowY = 0;
            int WindowWidth = 0, WindowHeight = 0;
        } m_UserData;

        void OnKeyDown(KeyDownEvent* event);
        void OnKeyUp(KeyUpEvent* event);

        void OnMouseMoved(MouseMovedEvent* event);
        void OnMouseButtonDown(MouseButtonDownEvent* event);
        void OnMouseButtonUp(MouseButtonUpEvent* event);
        void OnMouseScrolled(MouseScrolledEvent* event);

        void OnWindowMoved(WindowMovedEvent* event);
        void OnWindowResized(WindowResizedEvent* event);
    };
}