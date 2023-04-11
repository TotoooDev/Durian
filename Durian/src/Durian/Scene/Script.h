#include <lua.hpp>
#include <string>

namespace Durian
{
    class LuaScript
    {
    public:
        LuaScript(const std::string& path);

        void OnStart();
        void OnUpdate(double timestep);
        void OnEnd();

    private:
        bool CheckLua(int r);

        lua_State* m_State;
        std::string m_Path;
    };
}