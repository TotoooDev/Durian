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
		m_SceneBus.Subscribe(this, &Scene::OnKeyDown);
	    m_SceneBus.Subscribe(this, &Scene::OnWindowClosedEvent);
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

	void Scene::UpdateScene(double timestep)
	{
		// Execute scripts
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

		// Sounds
		// Application::Get().GetAudioEngine().Update();
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
							// Application::Get().GetAudioEngine().SetSoundDistance(sound, (unsigned char)distance);
							resetDistance = true;
						}

						Application::Get().GetAudioEngine().PlaySound(sound);

						// if (resetDistance)
						// 	Application::Get().GetAudioEngine().SetSoundDistance(sound, 0);
						
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
	}

	void Scene::RunSceneInEditor()
	{
		WindowSpecification spec(&m_SceneBus, "Durian In-Scene Player");
		Window window(spec);

		m_RunSceneInEditor = true;
		while (m_RunSceneInEditor)
		{
			window.PollEvents();

			UpdateScene(m_Timestep);

			window.Present();

			double currentFrame = (double)SDL_GetTicks() * 0.001f;
			m_Timestep = currentFrame - m_LastFrame;
			m_LastFrame = currentFrame;
		}
	}

	void Scene::OnViewportResize(float width, float height)
	{
		auto view = m_Registry.view<OrthoCameraComponent>();
		for (auto&& [id, cam] : view.each())
		{
			if (!cam.Resizable)
				continue;

			cam.Cam.xMin = -width / 2.0f;
			cam.Cam.xMax = width / 2.0f;
			cam.Cam.yMin = height / 2.0f;
			cam.Cam.yMax = -height / 2.0f;

			cam.Cam.UpdateMatrices();
		}
	}

	void Scene::OnKeyDown(KeyDownEvent* event)
	{
		if (event->Keycode == DURIAN_SCANCODE_ESCAPE)
        {
            DURIAN_LOG_INFO("grr");
            m_RunSceneInEditor = false;
        }
	}

	void Scene::OnWindowClosedEvent(WindowClosedEvent* event)
	{
        DURIAN_LOG_INFO("grr");
		m_RunSceneInEditor = false;
	}
	void Scene::OnWindowResizedEvent(WindowResizedEvent* event)
	{
		// if (event->Width == 0 && event->Height == 0)
		// 	m_Minimized = true;
		// else
		// 	m_Minimized = false;
		// glViewport(0, 0, m_Window.GetSpecification().Width, m_Window.GetSpecification().Height);
	}
}
