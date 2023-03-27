#pragma once
#include <Durian/Graphics/Camera.h>
#include <Durian/Event/Events.h>

namespace Durian
{
	class EditorCamera
	{
	public:
		EditorCamera(float viewportWidth, float viewportHeight, glm::vec3 pos = glm::vec3(0.0f));

		void OnUpdate(double timestep);
		void OnViewportResize(float width, float height);
		
		OrthoCamera GetOrthoCamera() { return m_Cam; }
		glm::mat4 GetProjectionMatrix() { return m_Cam.GetProjectionMatrix(); };
		glm::mat4 GetViewMatrix() { return m_View; };

		void ResetPos() { m_Pos = glm::vec3(0.0f); UpdateViewMatrix(); }

		bool Hovered = false;

	private:
		void UpdateViewMatrix();

		void OnMouseButtonDown(MouseButtonDownEvent* event);
		void OnMouseButtonUp(MouseButtonUpEvent* event);
		void OnMouseScrolled(MouseScrolledEvent* event);
		void OnMouseMoved(MouseMovedEvent* event);
		void OnKeyDown(KeyDownEvent* event);
		void OnKeyUp(KeyUpEvent* event);

		struct Inputs
		{
			bool LeftButton = false;
			bool MiddleButton = false;
			bool RightButton = false;
			bool Up = false;
			bool Down = false;
			bool Left = false;
			bool Right = false;
		} m_Inputs;

		glm::mat4 m_View;
		glm::vec3 m_Pos;
		glm::vec2 m_LastMousePos = glm::vec2(0.0f);
		OrthoCamera m_Cam;
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		float m_Speed;
	};
}