#include <pch.h>
#include <Panels/PropertiesPanel.h>
#include <Durian/Scene/Entity.h>

namespace Durian
{
	PropertiesPanel::PropertiesPanel(Entity* selected)
		: m_SelectedEntity(selected) {}

	void PropertiesPanel::Draw(bool* isOpen)
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

		DisplayAddComponentPopup();
		DisplayComponents();

		ImGui::End();
	}

	void PropertiesPanel::DisplayAddComponentPopup()
	{
		if (ImGui::Button("Add component"))
			ImGui::OpenPopup("Component list");

		if (ImGui::BeginPopup("Component list"))
		{
			if (ImGui::BeginMenu("Essentials"))
			{
				if (ImGui::MenuItem("Transform"))
					m_SelectedEntity->AddComponent<TransformComponent>();
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Graphics"))
			{
				if (ImGui::MenuItem("Sprite"))
					m_SelectedEntity->AddComponent<SpriteComponent>(CreateRef<Texture>("sprites/default.png"));
				if (ImGui::MenuItem("Ortho Camera"))
					m_SelectedEntity->AddComponent<OrthoCameraComponent>(OrthoCamera());
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Sound"))
			{
				if (ImGui::MenuItem("Sound Emitter"))
					m_SelectedEntity->AddComponent<SoundEmitterComponent>();
				if (ImGui::MenuItem("Sound Listener"))
					m_SelectedEntity->AddComponent<SoundListenerComponent>();
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}
	}

	void PropertiesPanel::DisplayComponents()
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
				DisplayRemoveComponent<TransformComponent>();

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
				auto& spriteComp = m_SelectedEntity->GetComponent<SpriteComponent>();
				DisplayRemoveComponent<SpriteComponent>();
				ImGui::Text("Current loaded sprite:");
				ImGui::Text(spriteComp.Tex->GetPath().c_str());
				if (ImGui::Button("Select sprite..."))
				{
					FileDialog dialog(FileDialogAction::Open, FileDialog::GetImagesFilter());
					std::string path = dialog.GetFileName();
					if (!path.empty())
						spriteComp.Tex = CreateRef<Texture>(path);
				}
				ImGui::TreePop();
			}
		}

		if (m_SelectedEntity->HasComponent<SoundEmitterComponent>())
		{
			if (ImGui::TreeNodeEx("Sound Emitter", flags))
			{
				auto& soundEmitComp = m_SelectedEntity->GetComponent<SoundEmitterComponent>();
				DisplayRemoveComponent<SoundEmitterComponent>();
				ImGui::Checkbox("Emit", &soundEmitComp.Emit);
				ImGui::Checkbox("Ignore distance", &soundEmitComp.IgnoreDistance);
				if (ImGui::Button("Attach new sound"))
				{
					FileDialog dialog(FileDialogAction::Open, FileDialog::GetSoundsFilter());
					std::string path = dialog.GetFileName();
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
				DisplayRemoveComponent<SoundListenerComponent>();
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
				DisplayRemoveComponent<OrthoCameraComponent>();

				int modified = 0;

				modified += ImGui::DragFloat("X Min", &camComp.Cam.xMin);
				modified += ImGui::DragFloat("X Max", &camComp.Cam.xMax);
				ImGui::Separator();
				modified += ImGui::DragFloat("Y Min", &camComp.Cam.yMin);
				modified += ImGui::DragFloat("Y Max", &camComp.Cam.yMax);
				ImGui::Separator();
				modified += ImGui::DragFloat("Near", &camComp.Cam.Near);
				modified += ImGui::DragFloat("Far", &camComp.Cam.Far);
				ImGui::Separator();
				ImGui::Checkbox("Primary camera", &camComp.PrimaryCamera);
				ImGui::Checkbox("Resizable", &camComp.Resizable);
				ImGui::Checkbox("Use", &camComp.Use);

				 if (modified > 0)
					camComp.Cam.UpdateMatrices();

				ImGui::TreePop();
			}
		}
	}
}