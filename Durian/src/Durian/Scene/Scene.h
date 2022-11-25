#pragma once

#include <string>
#include <entt/entt.hpp>

namespace Durian
{
	class Entity;

	class Scene
	{
	public:
		Entity CreateEntity(const std::string& name = "Unnamed Entity");
		void DeleteEntity(Entity entity);

		void UpdateScene(double timestep);

	private:
		entt::registry m_Registry;

		friend class Entity;
	};
}