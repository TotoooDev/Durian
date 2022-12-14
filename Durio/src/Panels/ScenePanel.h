#pragma once
#include <Durian/Scene/Scene.h>
#include <Durian/Scene/Components.h>
#include <imgui/imgui.h>

namespace Durian
{
	class ScenePanel
	{
	public:
		ScenePanel(Scene* scene = nullptr)
			: m_Scene(scene) {}

		void Draw(bool* isOpen)
		{
			if (!(*isOpen))
				return;

			ImGui::Begin("Scene View", isOpen);
			
			if (!m_Scene)
			{
				ImGui::End();
				return;
			}

			auto view = m_Scene->m_Registry.view<TagComponent>();
			for (auto&& [id, tag] : view.each())
			{
				if (ImGui::TreeNodeEx(tag.Tag.c_str(), ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_Leaf))
					ImGui::TreePop();
			}
			
			ImGui::End();
		}

	private:
		Scene* m_Scene;
	};
}