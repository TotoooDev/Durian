#include <pch.h>
#include <Durian/Core/Application.h>
#include <Durian/Scene/Scene.h>
#include <Durian/Scene/Entity.h>
#include <Durian/Scene/Components.h>
#include <Durian/Graphics/Renderer.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Durian
{
	Scene::Scene()
	{
	}

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

	Entity Scene::GetEntityByName(const std::string& tag)
	{
		auto view = m_Registry.view<TagComponent>();
		for (auto&& [id, entityTag] : view.each()) // Ew
		{
			if (tag == entityTag.Tag)
				return Entity(id, this);
		}
		return Entity(entt::null, nullptr);
	}

	void Scene::UpdateScene(double timestep, bool* runtime)
	{
		if (*runtime)
		{
			// Execute scripts
			auto scriptView = m_Registry.view<ScriptComponent>();
			for (auto&& [id, script] : scriptView.each())
			{
				if (!script.Script.WasStarted())
					script.Script.OnStart();
				script.Script.OnUpdate(timestep);
				if (m_Registry.any_of<TransformComponent>(id))
				{
					auto& transform = m_Registry.get<TransformComponent>(id);
					script.Script.GetTransformComponent(&transform);
				}
			}

			// Sounds
			auto listenerView = m_Registry.view<SoundListenerComponent>();
			for (auto&& [id, listener] : listenerView.each())
			{
				if (!listener.Listen)
				{
					// Tell the audio engine to stop playing sounds coming from this listener
					continue;
				}

				if (m_Registry.any_of<TransformComponent>(id) && !listener.IgnoreDistance)
				{
					auto emitterView = m_Registry.view<SoundEmitterComponent>();
					for (auto&& [id1, emitter] : emitterView.each())
					{
						if (!emitter.Emit)
						{
							// Tell the audio engine to stop playing sounds coming from this emitter
							continue;
						}

						// Play every sound in the queue
						while (!emitter.SoundQueue.empty())
						{
							Ref<Sound> sound = emitter.SoundQueue.front();
							bool resetDistance = false;

							// Set the distance if the emitter has a transform
							if (m_Registry.any_of<TransformComponent>(id1) && !emitter.IgnoreDistance)
							{
								glm::vec3 listenerPos = m_Registry.get<TransformComponent>(id).Translation;
								glm::vec3 emitterPos = m_Registry.get<TransformComponent>(id1).Translation;
								float distance = glm::distance(listenerPos, emitterPos);
								resetDistance = true;
							}

							Application::Get().GetAudioEngine().PlaySound(sound);

							emitter.SoundQueue.pop();
						}
					}
				}
				else
				{
					auto emitterView = m_Registry.view<SoundEmitterComponent>();
					for (auto&& [id1, emitter] : emitterView.each())
					{
						if (!emitter.Emit)
						{
							// Tell the audio engine to stop playing sounds coming from this emitter
							continue;
						}

						// Play every sound in the queue
						while (!emitter.SoundQueue.empty())
						{
							Ref<Sound> sound = emitter.SoundQueue.front();
							Application::Get().GetAudioEngine().PlaySound(sound);
							emitter.SoundQueue.pop();
						}
					}
				}
			}
			// Rendering
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
		else // If we are in the editor we render the scene using the "editor camera" m_Cam
		{
			Renderer::Get()->SetCurrentCamera(m_Cam, m_View);

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

	void Scene::OnViewportResize(float width, float height)
	{
		auto view = m_Registry.view<OrthoCameraComponent>();
		for (auto&& [id, cam] : view.each())
		{
			if (!cam.Resizable)
				continue;

			cam.Cam.xMin = 0;
			cam.Cam.xMax = width;
			cam.Cam.yMin = 0;
			cam.Cam.yMax = height;

			cam.Cam.UpdateMatrices();
		}
	}
}
