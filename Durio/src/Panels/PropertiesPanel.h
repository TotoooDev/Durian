#pragma once
#include <Durian/Scene/Entity.h>
#include <Durian/Scene/Components.h>
#include <Durian/Core/Application.h>
#include <Durian/Utils/FileManagement.h>
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

			if (!m_SelectedEntity->IsValid())
			{
				ImGui::Text("No entity selected");
				ImGui::Text("Select an entity to diplay its properties");
				ImGui::End();
				return;
			}

			if (ImGui::Button("Add component"))
				ImGui::OpenPopup("Component list");

			// TODO: Make this not look like shit
			// Graphic design is my ~passion~
			if (ImGui::BeginPopup("Component list"))
			{
				ImGui::Text("Essentials");
				if (ImGui::MenuItem("Transform"))
					m_SelectedEntity->AddComponent<TransformComponent>();
				ImGui::Separator();

				ImGui::Text("Graphics");
				if (ImGui::MenuItem("Sprite"))
					m_SelectedEntity->AddComponent<SpriteComponent>(CreateRef<Texture>("img.png"));
				ImGui::Separator();

				ImGui::Text("Cameras");
				if (ImGui::MenuItem("Ortho Camera"))
					m_SelectedEntity->AddComponent<OrthoCameraComponent>(OrthoCamera());
				ImGui::Separator();

				ImGui::Text("Sound");
				if (ImGui::MenuItem("Sound Emitter"))
					m_SelectedEntity->AddComponent<SoundEmitterComponent>();
				if (ImGui::MenuItem("Sound Listener"))
					m_SelectedEntity->AddComponent<SoundListenerComponent>();
				ImGui::Separator();

				ImGui::Text("Scripting");
				if (ImGui::MenuItem("Lua Script"))
					m_SelectedEntity->AddComponent<ScriptComponent>(*m_SelectedEntity);
				
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
					if (ImGui::Button("Select file..."))
					{
						std::string path = Utils::OpenFileDialog("Lua source file (*.lua)\0*.lua\0");
						if (!path.empty())
						{
							m_SelectedEntity->RemoveComponent<ScriptComponent>();
							m_SelectedEntity->AddComponent<ScriptComponent>(*m_SelectedEntity, path);
						}
					}
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
					if (ImGui::Button("Attach new sound"))
					{
						std::string path = Utils::OpenFileDialog(""); // TODO: Add a filter
						if (!path.empty())
						{
							SoundProperties prop;
							prop.Name = "New Sound" + std::to_string(soundEmitComp.AttachedSounds.size());
							Ref<Sound> sound = CreateRef<Sound>(path);
							prop.SoundVar = sound;
							soundEmitComp.AttachedSounds.push_back(prop);
						}
					}
					if (ImGui::TreeNodeEx("Attached sounds", ImGuiTreeNodeFlags_DefaultOpen))
					{
						for (auto& soundProp : soundEmitComp.AttachedSounds)
						{
							if (ImGui::TreeNodeEx(soundProp.Name.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
							{
								// TODO: Fix the focus problem
								char buf[128];
								strcpy(buf, soundProp.Name.c_str());
								if (ImGui::InputText("Name", buf, 128))
								{
									soundProp.Name = buf;
								}
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
