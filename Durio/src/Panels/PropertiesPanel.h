#pragma once
#include <Durian/Scene/Entity.h>
#include <Durian/Scene/Components.h>
#include <Durian/Core/Application.h>
#include <Utils/FileManagement.h>
#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

namespace Durian
{
	class PropertiesPanel
	{
	public:
		PropertiesPanel(Entity* selected = nullptr);

		void Draw(bool* isOpen);

	private:
		Entity* m_SelectedEntity;
		
		void DisplayAddComponentPopup();
		void DisplayComponents();

		template <typename T>
		void DisplayRemoveComponent()
		{
			if (ImGui::BeginPopupContextItem("RemoveComponent"))
			{
				if (ImGui::MenuItem("Remove component"))
					m_SelectedEntity->RemoveComponent<T>();
				ImGui::EndPopup();
			}
		}
	};
}
