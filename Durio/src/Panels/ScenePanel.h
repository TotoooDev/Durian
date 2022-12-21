#pragma once
#include <Durian/Scene/Scene.h>
#include <Durian/Scene/Components.h>
#include <imgui/imgui.h>

namespace Durian
{
	class ScenePanel
	{
	public:
		ScenePanel(Scene* scene = nullptr, Entity* selected = nullptr)
			: m_Scene(scene), m_SelectedEntity(selected) {}

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
				Entity ent(id, m_Scene);

				ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_FramePadding;
				
				if (m_SelectedEntity->GetID() == id)
        		{
          			flags |= ImGuiTreeNodeFlags_Selected;
        		}

				if (ImGui::TreeNodeEx(tag.Tag.c_str(), flags))
				{
          			if (ImGui::IsItemClicked() || ImGui::IsItemClicked(ImGuiMouseButton_Right))
						m_SelectedEntity = &ent;

					if (m_SelectedEntity->GetID() == id)
					{
						if (ImGui::BeginPopupContextItem())
						{
							if (ImGui::MenuItem("Delete Entity"))
							{
								// m_Scene->DeleteEntity(*m_SelectedEntity);
								// *m_SelectedEntity = { entt::null, nullptr };
							}
							ImGui::EndPopup();
						}
					}

					ImGui::TreePop();
				}
			}
			
			ImGui::End();
		}

	private:
		Scene* m_Scene;
		Entity* m_SelectedEntity;
	};
}
