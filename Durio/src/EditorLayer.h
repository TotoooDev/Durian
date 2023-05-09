#pragma once
#include <Durian/Core/Layer.h>
#include <Durian/Core/Ref.h>
#include <Durian/Scene/Scene.h>
#include <Durian/Scene/Entity.h>
#include <Durian/Graphics/Framebuffer.h>
#include <Durian/Event/Events.h>

#include <EditorCamera.h>
#include <Panels/ViewportPanel.h>
#include <Panels/ScenePanel.h>
#include <Panels/PropertiesPanel.h>
#include <Panels/LogPanel.h>
#include <Panels/RendererStatsPanel.h>

namespace Durian
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();

		void OnCreate() override;
		void OnUpdate(double timestep) override;
		void OnImGuiRender() override;

	private:
		void BeginDockSpace();
		void SetRuntime(bool runtime);

		void SaveAs();
		void Save();
		void Open();

		std::string m_ScenePath = "";
		Scene m_Scene;
		Ref<Framebuffer> m_Framebuffer;
		Entity* m_SelectedEntity;

		unsigned int m_CurrentCameraID = -1; // ID of the entity that has the camera used in the editor, -1 if we use m_EditorCamera
		EditorCamera m_EditorCamera;
		ImVec2 m_ViewportSize;

		ViewportPanel m_Viewport;
		ScenePanel m_SceneView;
		PropertiesPanel m_ComponentsView;
		LogPanel m_LogPanel;
		RendererStatsPanel m_StatsPanel;
		bool m_OpenViewport = true;
		bool m_OpenSceneView = true;
		bool m_OpenComponentsView = true;
		bool m_OpenLogPanel = true;
		bool m_OpenStatsPanel = true;

		bool m_Runtime = false;
		
		bool m_CtrlPressed = false;
		bool m_ShiftPressed = false;

		void OnKeyDown(KeyDownEvent* event);
		void OnKeyUp(KeyUpEvent* event);
	};
}