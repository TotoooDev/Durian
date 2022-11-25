#pragma once

#include <Durian/Scene/Scene.h>
#include <Durian/Core/Log.h>
#include <entt/entt.hpp>

namespace Durian
{
	class Entity
	{
	public:
		Entity(entt::entity identifier = entt::null, Scene* scene = nullptr)
			: m_Identifier(identifier), m_Scene(scene)
		{

		}

		template <typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			DURIAN_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return m_Scene->m_Registry.emplace<T>(m_Identifier, std::forward<Args>(args)...);
		}

		template <typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.any_of<T>(m_Identifier);
		}

		template <typename T>
		T& GetComponent()
		{
			DURIAN_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_Identifier);
		}

		template <typename T>
		void RemoveComponent()
		{
			DURIAN_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_Identifier);
		}

		bool IsValid()
		{
			return m_Identifier != entt::null && m_Scene != nullptr;
		}

		bool operator==(const Entity& ent) const
		{
			return this->m_Identifier == ent.m_Identifier && this->m_Scene == ent.m_Scene;
		}
		bool operator!=(const Entity& ent) const
		{
			return this->m_Identifier != ent.m_Identifier || this->m_Scene != ent.m_Scene;
		}

	private:
		entt::entity m_Identifier = entt::null;
		Scene* m_Scene = nullptr;

		friend class Scene;
	};
}