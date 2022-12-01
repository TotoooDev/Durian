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
		auto listenerView = m_Registry.view<SoundListenerComponent>();
		for (auto&& [id, listener] : listenerView.each())
		{
			if (!listener.Listen)
				continue;

			if (m_Registry.any_of<TransformComponent>(id) && !listener.IgnoreDistance)
			{
				auto emitterView = m_Registry.view<SoundEmitterComponent>();
				for (auto&& [id1, emitter] : emitterView.each())
				{
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
							Mix_SetDistance(sound->GetChannel(), (unsigned char)distance);
							resetDistance = true;
						}

						Mix_VolumeChunk(sound->GetChunk(), sound->GetVolume());
						Mix_PlayChannel(sound->GetChannel(), sound->GetChunk(), sound->GetLoops());

						if (resetDistance)
							Mix_SetDistance(sound->GetLoops(), 0);
						
						emitter.SoundQueue.pop();
					}
				}
			}
			else
			{
				auto emitterView = m_Registry.view<SoundEmitterComponent>();
				for (auto&& [id1, emitter] : emitterView.each())
				{
					// Play every sound in the queue
					while (!emitter.SoundQueue.empty())
					{
						Ref<Sound> sound = emitter.SoundQueue.front();
						Mix_Volume(sound->GetChannel(), sound->GetVolume());
						Mix_PlayChannel(sound->GetChannel(), sound->GetChunk(), sound->GetLoops());
						emitter.SoundQueue.pop();
					}
				}
			}
		}
	}
}