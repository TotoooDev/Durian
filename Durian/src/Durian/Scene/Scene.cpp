#include <pch.h>
#include <Scene/Scene.h>
#include <Scene/Entity.h>

namespace Durian
{
	Entity Scene::CreateEntity()
	{
		entt::entity id = m_Registry.create();
		return Entity(id, this);
	}

	void Scene::DeleteEntity(Entity entity)
	{
		DURIAN_ASSERT(entity.IsValid(), "Entity is not valid!");
		m_Registry.destroy(entity.m_Identifier);
	}
}