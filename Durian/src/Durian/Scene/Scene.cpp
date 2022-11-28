#include <pch.h>
#include <Durian/Scene/Scene.h>
#include <Durian/Scene/Entity.h>
#include <Durian/Scene/Components.h>
#include <Durian/Graphics/Renderer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Durian
{
	Entity Scene::CreateEntity(const std::string& name)
	{
		entt::entity id = m_Registry.create();
		m_Registry.emplace<TagComponent>(id, name);
		return Entity(id, this);
	}

	void Scene::DeleteEntity(Entity entity)
	{
		DURIAN_ASSERT(entity.IsValid(), "Entity is not valid!");
		m_Registry.destroy(entity.m_Identifier);
	}

	void Scene::UpdateScene(double timestep)
	{
		auto scriptView = m_Registry.view<ScriptComponent>();
		for (auto&& [id, script] : scriptView.each())
		{
			script.Script.OnUpdate(timestep);
			if (m_Registry.any_of<TransformComponent>(id))
			{
				auto& transform = m_Registry.get<TransformComponent>(id);
				script.Script.GetTransformComponent(&transform);
			}
		}

		auto camView = m_Registry.view<TransformComponent, OrthoCameraComponent>();
		for (auto&& [id, transform, camera] : camView.each())
		{
			if (!camera.Use)
				continue;
			
			// TODO: Store this somewhere and only update it when the camera gets updated
			glm::mat4 view = glm::lookAt(transform.Translation, transform.Translation + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			Renderer::Get()->SetCurrentCamera(camera.Cam, view);

			auto spriteView = m_Registry.view<TransformComponent, SpriteComponent>();
			for (auto&& [entity, transform, sprite] : spriteView.each())
			{
				if (sprite.UseColor)
					Renderer::Get()->DrawRectColor(transform.GetTransfrom(), sprite.Color);
				else
					Renderer::Get()->DrawRectTextured(transform.GetTransfrom(), sprite.Tex);
			}
		}
	}
}