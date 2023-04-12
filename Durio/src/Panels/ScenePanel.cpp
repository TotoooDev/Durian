#include <pch.h>
#include <Panels/ScenePanel.h>
#include <Durian/Scene/Entity.h>

namespace Durian
{
	ScenePanel::ScenePanel(Scene* scene, Entity* selected)
		: m_Scene(scene), m_SelectedEntity(selected) {}

	void ScenePanel::Draw(bool* isOpen)
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

			std::string name = tag.Tag.empty() ? "Unnamed entity" : tag.Tag;
			if (ImGui::TreeNodeEx(name.c_str(), flags))
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
			{
				Entity ent = m_Scene->CreateEntity("New Entity");
				*m_SelectedEntity = ent;
			}
			ImGui::EndPopup();
		}

		ImGui::End();
	}
}