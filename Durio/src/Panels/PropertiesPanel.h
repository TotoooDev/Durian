#pragma once
#include <Durian/Scene/Entity.h>
#include <Durian/Scene/Components.h>
#include <Durian/Core/Application.h>
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
				ImGui::End();
				return;
			}

			if (ImGui::Button("Add component"))
				ImGui::OpenPopup("Component list");

			if (ImGui::BeginPopup("Component list"))
			{
				if (ImGui::MenuItem("Transform"))
					m_SelectedEntity->AddComponent<TransformComponent>();
				if (ImGui::MenuItem("Sprite"))
					m_SelectedEntity->AddComponent<SpriteComponent>(CreateRef<Texture>("img.png"));

				ImGui::EndPopup();
			}

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
					strcpy(buf, tagComp.Tag.c_str());
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

			if (m_SelectedEntity->HasComponent<SpriteComponent>())
			{
				if (ImGui::TreeNodeEx("Sprite", flags))
				{
					ImGui::Text("coucou");
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
		

            if (m_SelectedEntity->HasComponent<SoundEmitterComponent>())
            {
                if (ImGui::TreeNodeEx("Sound Emitter", flags))
                {
                    auto& soundEmitComp = m_SelectedEntity->GetComponent<SoundEmitterComponent>();
					ImGui::Checkbox("Emit", &soundEmitComp.Emit);
                    ImGui::Checkbox("Ignore distance", &soundEmitComp.IgnoreDistance);
					if (ImGui::TreeNodeEx("Attached sounds", ImGuiTreeNodeFlags_DefaultOpen))
					{
						for (auto& soundProp : soundEmitComp.AttachedSounds)
						{
							if (ImGui::TreeNodeEx(soundProp.Name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
							{
								if (ImGui::SliderFloat("Volume", &soundProp.Volume, 0.0f, 1.0f))
									Application::Get().GetAudioEngine().SetVolume(soundProp.SoundVar, soundProp.Volume);
								ImGui::Checkbox("Loop", &soundProp.Loop);
								if (ImGui::Button("Play sound"))
									Application::Get().GetAudioEngine().PlaySound(soundProp.SoundVar);
								ImGui::SameLine();
								if (ImGui::Button("Stop sound"))
									Application::Get().GetAudioEngine().StopSound(soundProp.SoundVar);
								ImGui::TreePop();
							}
						}
						ImGui::TreePop();
					}
                    ImGui::TreePop();
                }
            }

            if (m_SelectedEntity->HasComponent<SoundListenerComponent>())
            {
                if (ImGui::TreeNodeEx("Sound Listener", flags))
                {
                    auto& soundListenComp = m_SelectedEntity->GetComponent<SoundListenerComponent>();
                    ImGui::Checkbox("Listen", &soundListenComp.Listen);
                    ImGui::Checkbox("Ignore distance", &soundListenComp.IgnoreDistance);
                    ImGui::TreePop();
                }
            }

			if (m_SelectedEntity->HasComponent<OrthoCameraComponent>())
			{
				if (ImGui::TreeNodeEx("Ortho Camera", flags))
				{
					auto& camComp = m_SelectedEntity->GetComponent<OrthoCameraComponent>();

					ImGui::DragFloat("X Min", &camComp.Cam.xMin);
					ImGui::SameLine();
					ImGui::DragFloat("X Max", &camComp.Cam.xMax);

					ImGui::DragFloat("Y Min", &camComp.Cam.yMin);
					ImGui::SameLine();
					ImGui::DragFloat("Y Max", &camComp.Cam.yMax);

					ImGui::DragFloat("Near", &camComp.Cam.Near);
					ImGui::SameLine();
					ImGui::DragFloat("Far", &camComp.Cam.Far);

					ImGui::Checkbox("Primary camera", &camComp.PrimaryCamera);
					ImGui::Checkbox("Resizable", &camComp.Resizable);
					ImGui::Checkbox("Use", &camComp.Use);

					ImGui::TreePop();
				}
			}
        }
	};
}
