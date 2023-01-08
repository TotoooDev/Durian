#pragma once

#include <Durian/Event/Events.h>
#include <Durian/Event/EventBus.h>
#include <string>
#include <entt/entt.hpp>

namespace Durian
{
	class Entity;

	class Scene
	{
	public:
		Scene();

		Entity CreateEntity(const std::string& name = "Unnamed Entity");
		void DeleteEntity(Entity entity);

		void UpdateScene(double timestep, bool* runtime);

		void OnViewportResize(float width, float height);

	private:

		entt::registry m_Registry;

		EventBus m_SceneBus;
        bool m_QuitRuntime = false;
		double m_Timestep = 0.0f;
		double m_LastFrame = 0.0f;

		void OnKeyDown(KeyDownEvent* event);

		friend class Entity;
		friend class ScenePanel;
	};
}
