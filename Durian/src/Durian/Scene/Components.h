#pragma once
#include <Durian/Core/Ref.h>
#include <Durian/Graphics/Texture.h>
#include <Durian/Graphics/Camera.h>
#include <Durian/Audio/Sound.h>
#include <Durian/Scene/Script.h>
#include <string>
#include <queue>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Durian
{
    struct TagComponent
	{
		std::string Tag;

		TagComponent(const std::string& tag = "")
			: Tag(tag) {}
		TagComponent(const TagComponent&) = default;
	};

    struct TransformComponent
	{
		glm::vec3 Translation;
		glm::vec3 Rotation;
		glm::vec3 Scale;

		TransformComponent(const glm::vec3& translation = glm::vec3(0.0f), const glm::vec3& rotation = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f))
			: Translation(translation), Rotation(rotation), Scale(scale) {}
		TransformComponent(const TransformComponent&) = default;

		glm::mat4 GetTransfrom()
		{
			glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
								 glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
								 glm::rotate(glm::mat4(1.0f), glm::radians(Rotation.z), glm::vec3(1.0f, 0.0f, 1.0f));

			return glm::translate(glm::mat4(1.0f), Translation) *
				   rotation *
				   glm::scale(glm::mat4(1.0f), Scale);
		}
	};

    struct SpriteComponent
    {
        bool Draw = true;
		bool UseColor = false;
        Ref<Texture> Tex;
		glm::vec4 Color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

        SpriteComponent(Ref<Texture> tex) 
            : Tex(tex) {}
		SpriteComponent(const SpriteComponent&) = default;
    };

    struct OrthoCameraComponent
    {
        bool PrimaryCamera = false;
		bool Use = true;
		bool Resizable = true;
        OrthoCamera Cam;

        OrthoCameraComponent(const OrthoCamera& cam)
			: Cam(cam) {}
		OrthoCameraComponent(const OrthoCameraComponent&) = default;
    };

	struct SoundEmitterComponent
	{
		bool Emit = true;
		bool IgnoreDistance = false;
		std::queue<Ref<Sound>> SoundQueue;
		std::vector<SoundProperties> AttachedSounds;

		SoundEmitterComponent() {}
		SoundEmitterComponent(const SoundEmitterComponent&) = default;
	};

	struct SoundListenerComponent
	{
		bool Listen = true;
		bool IgnoreDistance = false;

		SoundListenerComponent() {}
		SoundListenerComponent(const SoundListenerComponent&) = default;
	};

	struct ScriptComponent
	{
		LuaScript Script;
		ScriptComponent(const std::string& path, Entity ent)
			: Script(path, ent) {}
		ScriptComponent(const ScriptComponent&) = default;
	};
}
