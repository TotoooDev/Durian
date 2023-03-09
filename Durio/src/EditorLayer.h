#pragma once
#include <Durian/Core/Layer.h>
#include <Durian/Core/Ref.h>
#include <Durian/Scene/Scene.h>
#include <Durian/Scene/Entity.h>
#include <Durian/Graphics/Framebuffer.h>
#include <Durian/Event/Events.h>

#include <Panels/ViewportPanel.h>
#include <Panels/ScenePanel.h>
#include <Panels/PropertiesPanel.h>
#include <Panels/LogPanel.h>

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

		void Save();
		void Open();

		std::string m_ScenePath = "";
		Scene m_Scene;
		Ref<Framebuffer> m_Framebuffer;
		Entity* m_SelectedEntity;


		ImVec2 m_ViewportSize;

		ViewportPanel m_Viewport;
		ScenePanel m_SceneView;
		PropertiesPanel m_ComponentsView;
		LogPanel m_LogPanel;
		bool m_OpenViewport = true;
		bool m_OpenSceneView = true;
		bool m_OpenComponentsView = true;
		bool m_OpenLogPanel = true;

		bool m_Runtime = false;

		void OnKeyDown(KeyDownEvent* event);
	};
}