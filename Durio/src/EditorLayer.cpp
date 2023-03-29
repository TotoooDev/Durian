#include <EditorLayer.h>
#include <Durian/Core/Application.h>
#include <imgui/imgui.h>

#include <Durian/Scene/Components.h>
#include <Durian/Graphics/Renderer.h>
#include <Durian/Scene/Serializer.h>
#include <Utils/FileManagement.h>
#include <EditorSink.h>

namespace Durian
{
    EditorLayer::EditorLayer()
        : m_SceneView(&m_Scene, m_SelectedEntity), m_EditorCamera(0.0f, 0.0f)
    {
        Application::Get().GetEventBus()->Subscribe(this, &EditorLayer::OnKeyDown);
        Application::Get().GetEventBus()->Subscribe(this, &EditorLayer::OnKeyUp);
    }

	void EditorLayer::OnCreate() 
	{
        // Add the editor sink to spdlog
        auto sink = std::make_shared<EditorSink>(&m_LogPanel);
        sink->set_pattern("[%D %T] [%^%l%$] %v");
        spdlog::get("Default Logger")->sinks().push_back(sink);

		FramebufferSpecification spec;
		spec.Width = 800; spec.Height = 600;
		spec.AddTexture(FramebufferTexture::RGBA16);
		m_Framebuffer = CreateRef<Framebuffer>(spec);

        m_SelectedEntity = new Entity(entt::null, &m_Scene);

        m_Viewport = ViewportPanel(m_Framebuffer, &m_ViewportSize, &(m_EditorCamera.Hovered));
		m_SceneView = ScenePanel(&m_Scene, m_SelectedEntity);
        m_ComponentsView = PropertiesPanel(m_SelectedEntity);
	}

	void EditorLayer::OnUpdate(double timestep)
	{
        if (!m_Runtime)
            m_EditorCamera.OnUpdate(timestep);

		m_Framebuffer->Bind();
		Renderer::Get()->Clear(0.1f, 0.1f, 0.1f);

        m_Scene.CurrentCamera(m_EditorCamera.GetOrthoCamera(), m_EditorCamera.GetViewMatrix());
		m_Scene.UpdateScene(timestep, &m_Runtime);
	}

	void EditorLayer::OnImGuiRender() 
	{
		m_Framebuffer->Unbind();
		
        BeginDockSpace();

		ImGui::BeginMenuBar();
		if (ImGui::BeginMenu("File"))
		{
            if (ImGui::MenuItem("Save", "Ctrl+S"))
                Save();
            if (ImGui::MenuItem("Save as...", "Ctrl+Maj+S"))
                SaveAs();
            if (ImGui::MenuItem("Open...", "Ctrl+O"))
                Open();
            ImGui::Separator();
            if (ImGui::MenuItem("Close", "Alt+F4"))
                Application::Get().Stop();
			ImGui::EndMenu();
		}
        if (ImGui::BeginMenu("Scene"))
        {
            if (ImGui::MenuItem("Play scene", "F10"))
                SetRuntime(true);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Editor"))
        {
            if (ImGui::MenuItem("Reset camera position"))
                m_EditorCamera.ResetPos();
            ImGui::EndMenu();
        }
        if (m_Runtime)
        {
            ImGui::Separator();
            ImGui::Text("RUNTIME MODE IS ON, PRESS ESCAPE TO EXIT");
        }

		ImGui::EndMainMenuBar();

		ImVec2 oldSize = m_ViewportSize;
		m_Viewport.Draw(&m_OpenViewport);
		if (m_ViewportSize.x != oldSize.x || m_ViewportSize.y != oldSize.y)
		{
			m_Scene.OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
            m_EditorCamera.OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
		}

		m_SceneView.Draw(&m_OpenSceneView);
        m_ComponentsView.Draw(&m_OpenComponentsView);
        m_LogPanel.Draw(&m_OpenLogPanel);
        m_StatsPanel.Draw(&m_OpenStatsPanel);
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

    void EditorLayer::SetRuntime(bool runtime)
    {
        m_Runtime = runtime;
        if (m_Runtime)
        {
            // Set menu bar color to red to indicate runtime mode
            ImGuiStyle& style = ImGui::GetStyle();
            style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.501960813999176, 0.07450980693101883, 0.2549019753932953, 1.0);
            m_Viewport.SetTitle("Viewport (RUNTIME MODE)");
        }
        else
        {
            // Reset menu bar color
            ImGuiStyle& style = ImGui::GetStyle();
            style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.2000000029802322, 0.2196078449487686, 0.2666666805744171, 1.0);
            m_Viewport.SetTitle("Viewport");

            // Reload scene
            if (!m_ScenePath.empty())
            {
                m_Scene = Scene();
                Serializer serializer(&m_Scene);
                serializer.ImportJson(m_ScenePath);
                m_Scene.OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
                m_EditorCamera.OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
            }
        }
    }

    void EditorLayer::Save()
    {
        if (m_ScenePath.empty())
        {
            SaveAs();
            return;
        }
        Serializer serializer(&m_Scene);
        serializer.SerializeJson(m_ScenePath);
    }

    void EditorLayer::SaveAs()
    {
        FileDialog dialog(FileDialogAction::Save, FileDialog::GetDurianSceneFilter());
        Serializer serializer(&m_Scene);
        serializer.SerializeJson(m_ScenePath);
    }

    void EditorLayer::Open()
    {
        FileDialog dialog(FileDialogAction::Open, FileDialog::GetDurianSceneFilter());
        
        std::string path = dialog.GetFileName();
        if (!path.empty())
        {
            m_ScenePath = path;
            m_Scene = Scene();
            Serializer serializer(&m_Scene);
            serializer.ImportJson(path);
            m_Scene.OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
            m_EditorCamera.OnViewportResize(m_ViewportSize.x, m_ViewportSize.y);
        }
    }
    
    void EditorLayer::OnKeyDown(KeyDownEvent* event)
    {
        if (event->Keycode == DURIAN_SCANCODE_LCTRL || event->Keycode == DURIAN_SCANCODE_RCTRL)
            m_CtrlPressed = true;
        if (event->Keycode == DURIAN_SCANCODE_LSHIFT || event->Keycode == DURIAN_SCANCODE_RSHIFT)
            m_ShiftPressed = true;

        if (event->Keycode == DURIAN_SCANCODE_ESCAPE)
        {
            if (m_Runtime)
                SetRuntime(false);
        }

        if (event->Keycode == DURIAN_SCANCODE_F10)
            SetRuntime(true);

        if (m_CtrlPressed)
        {
            if (event->Keycode == DURIAN_SCANCODE_S)
            {
                if (m_ShiftPressed)
                    SaveAs();
                else
                    Save();
            }
            if (event->Keycode == DURIAN_SCANCODE_O)
                Open();
        }
    }
    
    void EditorLayer::OnKeyUp(KeyUpEvent* event)
    {
        if (event->Keycode == DURIAN_SCANCODE_LCTRL || event->Keycode == DURIAN_SCANCODE_RCTRL)
            m_CtrlPressed = false;
        if (event->Keycode == DURIAN_SCANCODE_LSHIFT || event->Keycode == DURIAN_SCANCODE_RSHIFT)
            m_ShiftPressed = false;
    }
}
