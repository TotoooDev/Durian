#pragma once
#include <Durian/Graphics/Camera.h>

namespace Durian
{
	class EditorCamera
	{
	public:
		EditorCamera(float viewportWidth, float viewportHeight);

		void OnViewportResize(float width, float height);
		void GetProjectionMatrix() { return m_Cam.GetProjectionMatrix(); };

	private:
		OrthoCamera m_Cam;
	};
}