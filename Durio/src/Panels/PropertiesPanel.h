#pragma once
#include <Durian/Scene/Entity.h>
#include <Durian/Scene/Components.h>
#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Durian
{
	class PropertiesPanel
	{
	public:
		PropertiesPanel(Entity* selected = nullptr)
			: m_SelectedEntity(selected) {}

		void Draw(bool* isOpen)
		{
			if (!(*isOpen))
				return;

			ImGui::Begin("Properties", isOpen);

			if (!m_SelectedEntity)
			{
				ImGui::Text("No entity selected");
				ImGui::Text("Select an entity to diplay its properties");
			}
			else
				DisplayComponents();

			ImGui::End();
		}

	private:
		Entity* m_SelectedEntity;
		
		void DisplayComponents()
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen;

			if (m_SelectedEntity->HasComponent<TagComponent>())
			{
				if (ImGui::TreeNodeEx("Tag", flags))
				{
					auto& tagComp = m_SelectedEntity->GetComponent<TagComponent>();
					char buf[128];
					strcpy_s(buf, 128, tagComp.Tag.c_str());
					if (ImGui::InputText("Name", buf, 128))
					{
						tagComp.Tag = buf;
					}
					ImGui::TreePop();
				}
			}

			if (m_SelectedEntity->HasComponent<TransformComponent>())
			{
				if (ImGui::TreeNodeEx("Transform", flags))
				{
					auto& transformComp = m_SelectedEntity->GetComponent<TransformComponent>();
					ImGui::DragFloat3("Position", glm::value_ptr(transformComp.Translation), 0.1f);
					ImGui::DragFloat3("Rotation", glm::value_ptr(transformComp.Rotation), 0.1f);
					ImGui::DragFloat3("Scale", glm::value_ptr(transformComp.Scale), 0.01f);
					ImGui::TreePop();
				}
			}

			if (m_SelectedEntity->HasComponent<ScriptComponent>())
			{
				if (ImGui::TreeNodeEx("Script", flags))
				{
					auto& scriptComp = m_SelectedEntity->GetComponent<ScriptComponent>();
					ImGui::Text("Path: %s", scriptComp.ScriptPath.c_str());
					if (ImGui::Button("Recompile script"))
						scriptComp.Script.Recompile();
					ImGui::TreePop();
				}
			}
		}
	};
}