#pragma once

#include <Durian/Graphics/Camera.h>
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

		// TODO: Change it to use a map or something like that
		Entity GetEntityByName(const std::string& tag);

		void UpdateScene(double timestep, bool* runtime);

		void CurrentCamera(OrthoCamera cam, glm::mat4 view) { m_Cam = cam; m_View = view; }
		void OnViewportResize(float width, float height);

		// TODO: Temporary, I need to find a better solution
		// This is only so the Lua library can have access to other entities in the scene since it doesn't have the definition of the other methods
		entt::registry* GetRegistry() { return &m_Registry; }

	private:
		entt::registry m_Registry;

		EventBus m_SceneBus;
        bool m_QuitRuntime = false;
		double m_Timestep = 0.0f;
		double m_LastFrame = 0.0f;

		glm::mat4 m_View;
		OrthoCamera m_Cam;

		friend class Entity;
		friend class ScenePanel;
		friend class Serializer;
	};
}
