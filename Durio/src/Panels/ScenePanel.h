#pragma once
#include <Durian/Scene/Scene.h>
#include <Durian/Scene/Components.h>
#include <imgui/imgui.h>

namespace Durian
{
	class ScenePanel
	{
	public:
		ScenePanel(Scene* scene, Entity* selected)
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
				
				if (m_SelectedEntity && m_SelectedEntity->GetID() == id)
        		{
          			flags |= ImGuiTreeNodeFlags_Selected;
        		}

				if (ImGui::TreeNodeEx(tag.Tag.c_str(), flags))
				{
					if (ImGui::IsItemClicked() || ImGui::IsItemClicked(ImGuiMouseButton_Right))
					{
						if (m_SelectedEntity->IsValid())
							*m_SelectedEntity = ent;
						else
							*m_SelectedEntity = Entity(ent.GetID(), m_Scene);
					}

					ImGui::TreePop();
				}
			}

			if (ImGui::BeginPopupContextWindow("Entity Context"))
			{
				if (ImGui::MenuItem("Add entity"))
					m_Scene->CreateEntity("New Entity");
				ImGui::EndPopup();
			}
			
			ImGui::End();
		}

	private:
		Scene* m_Scene;
		Entity* m_SelectedEntity;
	};
}
