#include <pch.h>
#include <Durian/Core/Application.h>
#include <Durian/Scene/Script.h>
#include <Durian/Scene/Components.h>

namespace Durian
{
    LuaScript::LuaScript(Entity ent, const std::string& filePath)
        : m_Path(filePath)
    {
        m_State = luaL_newstate();
        luaL_openlibs(m_State);
        if (!CheckLua(luaL_dofile(m_State, m_Path.c_str())))
            return;

        m_UserData.Ent = ent;

        lua_pushlightuserdata(m_State, &m_UserData);
        lua_setglobal(m_State, "Durian_EntityPointer");

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
        lua_register(m_State, "Durian_AttachTransform", [](lua_State* state)
        {
            lua_getglobal(state, "Durian_EntityPointer");
            UserData* data = (UserData*)lua_touserdata(state, -1);
            data->Ent.AddComponent<TransformComponent>();
            return 0;
        });
        lua_register(m_State, "Durian_DetachTransform", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_EntityPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                data->Ent.RemoveComponent<TransformComponent>();
                return 0;
            });
        lua_register(m_State, "Durian_EventKeyDown", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_EntityPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                lua_pushnumber(state, data->KeyDown);
                return 1;
            });
        lua_register(m_State, "Durian_EventKeyUp", [](lua_State* state)
            {
                lua_getglobal(state, "Durian_EntityPointer");
                UserData* data = (UserData*)lua_touserdata(state, -1);
                lua_pushnumber(state, data->KeyUp);
                return 1;
            });

        Application::Get().GetEventBus()->Subscribe(this, &LuaScript::OnKeyDown);
        Application::Get().GetEventBus()->Subscribe(this, &LuaScript::OnKeyUp);

        OnStart();
    }

    void LuaScript::OnStart()
    {
        lua_getglobal(m_State, "OnStart");
        if (lua_isfunction(m_State, -1))
            CheckLua(lua_pcall(m_State, 0, 0, 0));
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

    void LuaScript::GetTransformComponent(TransformComponent* comp)
    {
        glm::vec3 translation(0.0f), scale(0.0f), rotation(0.0f);

        lua_getglobal(m_State, "Transform");
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
}