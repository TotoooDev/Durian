#pragma once
#include <Durian/Scene/Scene.h>
#include <nlohmann/json.hpp>
#include <string>

namespace Durian
{
	class Serializer
	{
	public:
		Serializer(Scene* scene)
			: m_Scene(scene) {}

		void SerializeJson(const std::string& path);
		void ImportJson(const std::string& path);

	private:
		void SerializeEntity(Entity entity, nlohmann::json& entityJson);
		void DeserializeEntity(Entity& entity, nlohmann::json& entityJson);

		void SerializeVec3(const glm::vec3& vec, nlohmann::json& json);
		glm::vec3 DeserializeVec3(nlohmann::json& json);
		void SerializeVec4(const glm::vec4& vec, nlohmann::json& json);
		glm::vec4 DeserializeVec4(nlohmann::json& json);

		Scene* m_Scene;
	};
}