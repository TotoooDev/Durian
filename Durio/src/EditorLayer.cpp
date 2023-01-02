#include <EditorLayer.h>
#include <Durian/Core/Application.h>
#include <imgui/imgui.h>

#include <Durian/Scene/Components.h>
#include <Durian/Graphics/Renderer.h>

namespace Durian
{
	void EditorLayer::OnCreate() 
	{
		FramebufferSpecification spec;
		spec.Width = 800; spec.Height = 600;
		spec.AddTexture(FramebufferTexture::RGBA16);
		m_Framebuffer = CreateRef<Framebuffer>(spec);

        m_SelectedEntity = &m_SpriteEntity;

		m_Viewport = ViewportPanel(m_Framebuffer, &m_ViewportSize);
		m_SceneView = ScenePanel(&m_Scene, m_SelectedEntity);
        m_ComponentsView = PropertiesPanel(m_SelectedEntity);

		m_SpriteEntity = m_Scene.CreateEntity("Sprite");
		m_SpriteEntity.AddComponent<ScriptComponent>(m_SpriteEntity, "Script.lua");
        auto& soundEmitter = m_SpriteEntity.AddComponent<SoundEmitterComponent>();
        Ref<Sound> sound = CreateRef<Sound>("grr.wav");
        // soundEmitter.SoundQueue.push(sound);
        SoundProperties prop;
        prop.Sound = sound;
        soundEmitter.AttachedSounds.push_back(prop);

		m_CameraEntity = m_Scene.CreateEntity("Camera");
		m_CameraEntity.AddComponent<TransformComponent>();
		OrthoCamera cam;
		m_CameraEntity.AddComponent<OrthoCameraComponent>(cam);
		m_CameraEntity.AddComponent<SoundListenerComponent>();
	}

	void EditorLayer::OnUpdate(double timestep)
	{
		m_Framebuffer->Bind();
		Renderer::Get()->Clear(0.1f, 0.1f, 0.1f);

		m_Scene.UpdateScene(timestep);
	}

	void EditorLayer::OnImGuiRender() 
	{
		m_Framebuffer->Unbind();
		
        BeginDockSpace();

		ImGui::BeginMenuBar();
		if (ImGui::BeginMenu("File"))
		{
            if (ImGui::MenuItem("Close", "Alt+F4"))
                Application::Get().Stop();
			ImGui::EndMenu();
		}
        if (ImGui::BeginMenu("Scene"))
        {
            if (ImGui::MenuItem("Play scene"))
                m_Scene.RunSceneInEditor();
            ImGui::EndMenu();
        }
		ImGui::EndMainMenuBar();

		ImVec2 oldSize = m_ViewportSize;
		m_Viewport.Draw(&m_OpenViewport);
		if (m_ViewportSize.x != oldSize.x || m_ViewportSize.y != oldSize.y)
		{
			m_Scene.OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
		}

		m_SceneView.Draw(&m_OpenSceneView);
        m_ComponentsView.Draw(&m_OpenComponentsView);
	}

    void EditorLayer::BeginDockSpace()
    {
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace", nullptr, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
    }
}
