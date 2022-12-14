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

namespace Durian
{
	class EditorLayer : public Layer
	{
	public:
		void OnCreate() override;
		void OnUpdate(double timestep) override;
		void OnImGuiRender() override;

	private:
		void BeginDockSpace();

		Scene m_Scene;
		Entity m_SpriteEntity;
		Entity m_CameraEntity;
		Ref<Framebuffer> m_Framebuffer;

		Entity* m_SelectedEntity;

		ImVec2 m_ViewportSize;

		bool m_OpenViewport = true;
		ViewportPanel m_Viewport;
		bool m_OpenSceneView = true;
		ScenePanel m_SceneView;
		bool m_OpenComponentsView = true;
		PropertiesPanel m_ComponentsView;

		bool m_Runtime = false;
	};
}