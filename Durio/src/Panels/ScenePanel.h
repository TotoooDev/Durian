#pragma once
#include <Durian/Scene/Scene.h>
#include <Durian/Scene/Components.h>
#include <imgui/imgui.h>

namespace Durian
{
	class ScenePanel
	{
	public:
		ScenePanel(Scene* scene, Entity* selected);

		void Draw(bool* isOpen);

	private:
		Scene* m_Scene;
		Entity* m_SelectedEntity;
	};
}
