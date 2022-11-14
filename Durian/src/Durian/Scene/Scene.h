#pragma once

#include <entt/entt.hpp>

namespace Durian
{
	class Entity;

	class Scene
	{
	public:
		Entity CreateEntity();
		void DeleteEntity(Entity entity);

	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}