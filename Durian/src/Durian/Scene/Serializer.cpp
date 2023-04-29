#include <pch.h>
#include <Durian/Scene/Serializer.h>
#include <Durian/Scene/Components.h>
#include <Durian/Scene/Entity.h>
#include <nlohmann/json.hpp>
#include <fstream>

namespace Durian
{
	void Serializer::SerializeJson(const std::string& path)
	{
		nlohmann::json json;

		nlohmann::json& entities = json["scene"]["entities"];
		int num = 0;
		auto& registry = m_Scene->m_Registry;
		registry.each([&](auto entity)
			{
				Entity ent(entity, m_Scene);
				if (!ent.IsValid())
					return;

				SerializeEntity(ent, entities[num]);
				num++;
			});

		std::ofstream file(path);
		file << std::setw(4) << json;
	}

	void Serializer::ImportJson(const std::string& path)
	{
		std::ifstream file;
		file.open(path);
		nlohmann::json json = nlohmann::json::parse(file);
		file.close();

		if (!json.contains("scene"))
		{
			spdlog::error("{0} is not a valid TOE scene!", path);
			return;
		}

		// m_Scene->Name = json["scene"]["name"];

		unsigned int numEntities = json["scene"]["entities"].size();
		for (unsigned int i = 0; i < numEntities; i++)
		{
			auto ent = m_Scene->CreateEntity();
			DeserializeEntity(ent, json["scene"]["entities"][i]);
		}
	}
	
	void Serializer::SerializeEntity(Entity entity, nlohmann::json& entityJson)
	{
		if (entity.HasComponent<TagComponent>())
		{
			auto& tagComp = entity.GetComponent<TagComponent>();
			entityJson["tag"]["tag"] = tagComp.Tag.c_str();
		}

		if (entity.HasComponent<TransformComponent>())
		{
			auto& transformComp = entity.GetComponent<TransformComponent>();
			SerializeVec3(transformComp.Translation, entityJson["transform"]["translation"]);
			SerializeVec3(transformComp.Rotation, entityJson["transform"]["rotation"]);
			SerializeVec3(transformComp.Scale, entityJson["transform"]["scale"]);
		}

		if (entity.HasComponent<SpriteComponent>())
		{
			auto& spriteComp = entity.GetComponent<SpriteComponent>();
			entityJson["sprite"]["draw"] = spriteComp.Draw;
			entityJson["sprite"]["use_color"] = spriteComp.UseColor;
			SerializeVec4(spriteComp.Color, entityJson["sprite"]["color"]);
			entityJson["sprite"]["path"] = spriteComp.Tex->GetPath();
		}

		if (entity.HasComponent<OrthoCameraComponent>())
		{
			auto& camComp = entity.GetComponent<OrthoCameraComponent>();
			entityJson["ortho_cam"]["primary"] = camComp.PrimaryCamera;
			entityJson["ortho_cam"]["use"] = camComp.Use;
			entityJson["ortho_cam"]["resizable"] = camComp.Resizable;

			entityJson["ortho_cam"]["cam"]["x_min"] = camComp.Cam.xMin;
			entityJson["ortho_cam"]["cam"]["x_max"] = camComp.Cam.xMax;
			entityJson["ortho_cam"]["cam"]["y_min"] = camComp.Cam.yMin;
			entityJson["ortho_cam"]["cam"]["y_max"] = camComp.Cam.yMax;
			entityJson["ortho_cam"]["cam"]["near"] = camComp.Cam.Near;
			entityJson["ortho_cam"]["cam"]["far"] = camComp.Cam.Far;
		}

		if (entity.HasComponent<SoundEmitterComponent>())
		{
			auto& emitComp = entity.GetComponent<SoundEmitterComponent>();
			entityJson["sound_emitter"]["emit"] = emitComp.Emit;
			entityJson["sound_emitter"]["ignore_distance"] = emitComp.IgnoreDistance;

			int num = 0;
			nlohmann::json& propJson = entityJson["sound_emitter"]["attached_sounds"];
			for (auto& prop : emitComp.AttachedSounds)
			{
				propJson[num]["volume"] = prop.Volume;
				propJson[num]["loop"] = prop.Loop;
				propJson[num]["name"] = prop.Name;
				propJson[num]["path"] = prop.SoundVar->GetPath();
				num++;
			}
		}

		if (entity.HasComponent<SoundListenerComponent>())
		{
			auto& listenComp = entity.GetComponent<SoundListenerComponent>();
			entityJson["sound_listener"]["listen"] = listenComp.Listen;
			entityJson["sound_listener"]["ignore_distance"] = listenComp.IgnoreDistance;
		}

		if (entity.HasComponent<ScriptComponent>())
		{
			auto& scriptComp = entity.GetComponent<ScriptComponent>();
			entityJson["lua_script"]["path"] = scriptComp.Script.GetPath();
		}
	}
	void Serializer::DeserializeEntity(Entity& entity, nlohmann::json& entityJson)
	{
		// Tag and transform components are created along with the entity so we dont need to create them
		// We should always have a tag component attached to an entity
		if (entityJson.contains("tag"))
		{
			entity.GetComponent<TagComponent>().Tag = entityJson["tag"]["tag"];
		}
		else
		{
			entity.GetComponent<TagComponent>().Tag = "Unnamed Entity";
		}

		if (entityJson.contains("transform"))
		{
			auto& transformComp = entity.AddComponent<TransformComponent>();
			transformComp.Translation = DeserializeVec3(entityJson["transform"]["translation"]);
			transformComp.Rotation = DeserializeVec3(entityJson["transform"]["rotation"]);
			transformComp.Scale = DeserializeVec3(entityJson["transform"]["scale"]);
		}

		if (entityJson.contains("sprite"))
		{
			Ref<Texture> texture = CreateRef<Texture>(entityJson["sprite"]["path"]);
			auto& spriteComp = entity.AddComponent<SpriteComponent>(texture);
			spriteComp.Draw = entityJson["sprite"]["draw"];
			spriteComp.UseColor = entityJson["sprite"]["use_color"];
			spriteComp.Color = DeserializeVec4(entityJson["sprite"]["color"]);
		}

		if (entityJson.contains("ortho_cam"))
		{
			OrthoCamera cam;
			cam.xMin = entityJson["ortho_cam"]["cam"]["x_min"];
			cam.xMax = entityJson["ortho_cam"]["cam"]["x_max"];
			cam.yMin = entityJson["ortho_cam"]["cam"]["y_min"];
			cam.yMax = entityJson["ortho_cam"]["cam"]["y_max"];
			cam.Near = entityJson["ortho_cam"]["cam"]["near"];
			cam.Far = entityJson["ortho_cam"]["cam"]["far"];
			auto& camComp = entity.AddComponent<OrthoCameraComponent>(cam);

			camComp.PrimaryCamera = entityJson["ortho_cam"]["primary"];
			camComp.Use = entityJson["ortho_cam"]["use"];
			camComp.Resizable = entityJson["ortho_cam"]["resizable"];
		}

		if (entityJson.contains("sound_emitter"))
		{
			auto& emitComp = entity.AddComponent<SoundEmitterComponent>();
			emitComp.Emit = entityJson["sound_emitter"]["emit"];
			emitComp.IgnoreDistance = entityJson["sound_emitter"]["ignore_distance"];

			nlohmann::json& propJson = entityJson["sound_emitter"]["attached_sounds"];
			for (unsigned int i = 0; i < propJson.size(); i++)
			{
				SoundProperties prop;
				Ref<Sound> sound = CreateRef<Sound>(propJson[i]["path"]);
				prop.SoundVar = sound;

				prop.Volume = propJson[i]["volume"];
				prop.Loop = propJson[i]["loop"];
				prop.Name = propJson[i]["name"];

				emitComp.AttachedSounds.push_back(prop);
			}
		}

		if (entityJson.contains("sound_listener"))
		{
			auto& listenComp = entity.AddComponent<SoundListenerComponent>();
			listenComp.Listen = entityJson["sound_listener"]["listen"];
			listenComp.IgnoreDistance = entityJson["sound_listener"]["ignore_distance"];
		}

		if (entityJson.contains("lua_script"))
		{
			auto& scriptComp = entity.AddComponent<ScriptComponent>(entityJson["lua_script"]["path"], entity);
		}
	}

	void Serializer::SerializeVec3(const glm::vec3& vec, nlohmann::json& json)
	{
		json["x"] = vec.x;
		json["y"] = vec.y;
		json["z"] = vec.z;
	}

	glm::vec3 Serializer::DeserializeVec3(nlohmann::json& json)
	{
		return glm::vec3(json["x"], json["y"], json["z"]);
	}

	void Serializer::SerializeVec4(const glm::vec4& vec, nlohmann::json& json)
	{
		json["x"] = vec.x;
		json["y"] = vec.y;
		json["z"] = vec.z;
		json["w"] = vec.w;
	}

	glm::vec4 Serializer::DeserializeVec4(nlohmann::json& json)
	{
		return glm::vec4(json["x"], json["y"], json["z"], json["w"]);
	}
}