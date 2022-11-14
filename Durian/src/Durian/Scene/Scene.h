#pragma once

#include <Scene/Entity.h>
#include <entt/entt.hpp>

namespace Durian
{
	class Scene
	{
	public:
		Entity CreateEntity();
		void DeleteEntity(Entity entity);

	private:
		entt::registry m_Registry;
	};
}