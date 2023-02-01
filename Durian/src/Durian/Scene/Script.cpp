#include <pch.h>
#include <Durian/Core/Ref.h>
#include <Durian/Core/Application.h>
#include <Durian/Scene/Script.h>
#include <Durian/Scene/Components.h>
#include <algorithm>

namespace Durian
{
    LuaScript::LuaScript(Entity ent, const std::string& filePath)
        : m_Path(filePath)
    {
        Application::Get().GetEventBus()->Subscribe(this, &LuaScript::OnKeyDown);
        Application::Get().GetEventBus()->Subscribe(this, &LuaScript::OnKeyUp);
        Application::Get().GetEventBus()->Subscribe(this, &LuaScript::OnMouseMoved);
        Application::Get().GetEventBus()->Subscribe(this, &LuaScript::OnMouseButtonDown);
        Application::Get().GetEventBus()->Subscribe(this, &LuaScript::OnMouseButtonUp);
        Application::Get().GetEventBus()->Subscribe(this, &LuaScript::OnMouseScrolled);
        Application::Get().GetEventBus()->Subscribe(this, &LuaScript::OnWindowMoved);
        Application::Get().GetEventBus()->Subscribe(this, &LuaScript::OnWindowResized);

        m_UserData.WindowWidth = Application::Get().GetWindowSpec().Width;
        m_UserData.WindowHeight = Application::Get().GetWindowSpec().Height;
        m_UserData.Ent = ent;

        Create();
    }

    LuaScript::~LuaScript()
    {
        lua_close(m_State);
    }

    void LuaScript::OnStart()
    {
        lua_getglobal(m_State, "OnStart");
        if (lua_isfunction(m_State, -1))
            CheckLua(lua_pcall(m_State, 0, 0, 0));
        m_WasStarted = true;
    }

    void LuaScript::OnUpdate(float timestep)
    {
        lua_getglobal(m_State, "OnUpdate");
        if (lua_isfunction(m_State, -1))
        {
            lua_pushnumber(m_State, timestep);
            CheckLua(lua_pcall(m_State, 1, 0, 0));
        }
    }

    void LuaScript::Recompile()
    {
        lua_close(m_State);
        Create();
    }

    void LuaScript::GetTransformComponent(TransformComponent* comp)
    {
        glm::vec3 translation(0.0f), scale(0.0f), rotation(0.0f);

        lua_getglobal(m_State, "Durian");
        if (lua_istable(m_State, -1))
        {
            lua_pushstring(m_State, "Transform");
            lua_gettable(m_State, -2);
            if (lua_istable(m_State, -1))
            {
                lua_pushstring(m_State, "Translation");
                lua_gettable(m_State, -2);
                if (lua_istable(m_State, -1))
                {
                    lua_pushstring(m_State, "x");
                    lua_gettable(m_State, -2);
                    translation.x = lua_tonumber(m_State, -1);
                    lua_pop(m_State, 1);

                    lua_pushstring(m_State, "y");
                    lua_gettable(m_State, -2);
                    translation.y = lua_tonumber(m_State, -1);
                    lua_pop(m_State, 1);

                    lua_pushstring(m_State, "z");
                    lua_gettable(m_State, -2);
                    translation.z = lua_tonumber(m_State, -1);
                    lua_pop(m_State, 1);

                    comp->Translation = translation;
                }
                lua_pop(m_State, 1);

                lua_pushstring(m_State, "Scale");
                lua_gettable(m_State, -2);
                if (lua_istable(m_State, -1))
                {
                    lua_pushstring(m_State, "x");
                    lua_gettable(m_State, -2);
                    scale.x = lua_tonumber(m_State, -1);
                    lua_pop(m_State, 1);

                    lua_pushstring(m_State, "y");
                    lua_gettable(m_State, -2);
                    scale.y = lua_tonumber(m_State, -1);
                    lua_pop(m_State, 1);

                    lua_pushstring(m_State, "z");
                    lua_gettable(m_State, -2);
                    scale.z = lua_tonumber(m_State, -1);
                    lua_pop(m_State, 1);

                    comp->Scale = scale;
                }
                lua_pop(m_State, 1);

                lua_pushstring(m_State, "Rotation");
                lua_gettable(m_State, -2);
                if (lua_istable(m_State, -1))
                {
                    lua_pushstring(m_State, "x");
                    lua_gettable(m_State, -2);
                    rotation.x = lua_tonumber(m_State, -1);
                    lua_pop(m_State, 1);

                    lua_pushstring(m_State, "y");
                    lua_gettable(m_State, -2);
                    rotation.y = lua_tonumber(m_State, -1);
                    lua_pop(m_State, 1);

                    lua_pushstring(m_State, "z");
                    lua_gettable(m_State, -2);
                    rotation.z = lua_tonumber(m_State, -1);
                    lua_pop(m_State, 1);

                    comp->Rotation = rotation;
                }
                lua_pop(m_State, 1);
            }
        }
    }

    void LuaScript::Create()
    {
        m_State = luaL_newstate();
        luaL_openlibs(m_State);
        if (!CheckLua(luaL_dofile(m_State, m_Path.c_str())))
            return;

        lua_pushlightuserdata(m_State, &m_UserData);
        lua_setglobal(m_State, "Durian_DataPointer");

        SetCppFunctions();
    }

    bool LuaScript::CheckLua(int r)
    {
        if (r != LUA_OK)
        {
            std::string error = lua_tostring(m_State, -1);
            DURIAN_LOG_ERROR("[LUA]: {}", error);
            return false;
        }
        return true;
    }

    void LuaScript::SetCppFunctions()
    {
        // Logging
        lua_register(m_State, "Durian_LogInfo", [](lua_State* state)
            {
                DURIAN_LOG_INFO(lua_tostring(state, 1));
                return 0;
            });
        lua_register(m_State, "Durian_LogWarn", [](lua_State* state)
            {
                DURIAN_LOG_WARN(lua_tostring(state, 1));
                return 0;
            });
        lua_register(m_State, "Durian_LogError", [](lua_State* state)
            {
                DURIAN_LOG_ERROR(lua_tostring(state, 1));
                return 0;
            });

        // Components
        // Transform
        lua_register(m_State, "Durian_AttachTransform", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                data->Ent.AddComponent<TransformComponent>();
                return 0;
            });
        lua_register(m_State, "Durian_DetachTransform", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                data->Ent.RemoveComponent<TransformComponent>();
                return 0;
            });
        // Sprite
        lua_register(m_State, "Durian_AttachSprite", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                const char* texPath = lua_tostring(state, 1);
                data->Ent.AddComponent<SpriteComponent>(CreateRef<Texture>(texPath));
                return 0;
            });
        lua_register(m_State, "Durian_DetachSprite", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                data->Ent.RemoveComponent<SpriteComponent>();
                return 0;
            });
        // Sound emitter
        lua_register(m_State, "Durian_AttachSoundEmitter", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                const char* texPath = lua_tostring(state, 1);
                data->Ent.AddComponent<SoundEmitterComponent>();
                return 0;
            });
        lua_register(m_State, "Durian_DetachSoundEmitter", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                data->Ent.RemoveComponent<SpriteComponent>();
                return 0;
            });
        lua_register(m_State, "Durian_SoundLoad", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                const char* path = lua_tostring(state, 1);
                Ref<Sound> sound = CreateRef<Sound>(path);
                auto& soundEmitComp = data->Ent.GetComponent<SoundEmitterComponent>();
                SoundProperties prop;
                prop.SoundVar = sound;
                soundEmitComp.AttachedSounds.push_back(prop);
                lua_pushnumber(state, soundEmitComp.AttachedSounds.size() - 1);
                return 1;
            });
        lua_register(m_State, "Durian_SoundPlay", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                unsigned int soundId = (unsigned int)lua_tonumber(state, 1);
                float volume = (float)lua_tonumber(state, 2);
                auto& soundEmitComp = data->Ent.GetComponent<SoundEmitterComponent>();
                Ref<Sound> sound = soundEmitComp.AttachedSounds[soundId].SoundVar;
                soundEmitComp.SoundQueue.push(sound);
                return 0;
            });
        lua_register(m_State, "Durian_SoundVolume", [](lua_State* state) // Does not work atm
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                unsigned int soundId = (unsigned int)lua_tonumber(state, 1);
                float volume = (float)lua_tonumber(state, 2);
                auto& emitter = data->Ent.GetComponent<SoundEmitterComponent>();
                Ref<Sound> sound = emitter.AttachedSounds[soundId].SoundVar;
                Application::Get().GetAudioEngine().SetVolume(sound, volume);
                emitter.AttachedSounds[soundId].Volume = volume;
                return 0;
            });

        // Events
        // Keyboard
        lua_register(m_State, "Durian_EventKeyDown", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                lua_pushnumber(state, data->KeyDown);
                return 1;
            });
        lua_register(m_State, "Durian_EventKeyUp", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                lua_pushnumber(state, data->KeyUp);
                return 1;
            });
        // Mouse
        lua_register(m_State, "Durian_EventMouseMoved", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                lua_pushnumber(state, data->MouseX);
                lua_pushnumber(state, data->MouseY);
                return 2;
            });
        lua_register(m_State, "Durian_EventMouseButtonDown", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                lua_pushnumber(state, data->ButtonDown);
                return 1;
            });
        lua_register(m_State, "Durian_EventMouseButtonUp", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                lua_pushnumber(state, data->ButtonUp);
                return 1;
            });
        lua_register(m_State, "Durian_EventMouseScrolled", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                lua_pushnumber(state, data->ScrollX);
                lua_pushnumber(state, data->ScrollY);
                return 2;
            });
        // Window
        lua_register(m_State, "Durian_EventWindowPos", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                lua_pushnumber(state, data->WindowX);
                lua_pushnumber(state, data->WindowY);
                return 2;
            });
        lua_register(m_State, "Durian_EventWindowSize", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_DataPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                lua_pushnumber(state, data->WindowWidth);
                lua_pushnumber(state, data->WindowHeight);
                return 2;
            });
    }

    void LuaScript::OnKeyDown(KeyDownEvent* event)
    {
        m_UserData.KeyDown = event->Keycode;
        m_UserData.KeyUp = 0;
    }
    void LuaScript::OnKeyUp(KeyUpEvent* event)
    {
        m_UserData.KeyDown = 0;
        m_UserData.KeyUp = event->Keycode;
    }

    void LuaScript::OnMouseMoved(MouseMovedEvent* event)
    {
        m_UserData.MouseX = event->x;
        m_UserData.MouseY = event->y;
    }
    void LuaScript::OnMouseButtonDown(MouseButtonDownEvent* event)
    {
        m_UserData.ButtonDown = event->Button;
        m_UserData.ButtonUp = 0;
    }
    void LuaScript::OnMouseButtonUp(MouseButtonUpEvent* event)
    {
        m_UserData.ButtonDown = 0;
        m_UserData.ButtonUp = event->Button;
    }
    void LuaScript::OnMouseScrolled(MouseScrolledEvent* event)
    {
        m_UserData.ScrollX = event->xOffset;
        m_UserData.ScrollY = event->yOffset;
    }

    void LuaScript::OnWindowMoved(WindowMovedEvent* event)
    {
        m_UserData.WindowX = event->x;
        m_UserData.WindowY = event->y;
    }
    void LuaScript::OnWindowResized(WindowResizedEvent* event)
    {
        m_UserData.WindowWidth = event->Width;
        m_UserData.WindowHeight = event->Height;
    }
}
