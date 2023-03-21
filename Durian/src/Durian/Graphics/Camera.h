#pragma once
#include <glm/glm.hpp>

namespace Durian
{
	class OrthoCamera
	{
	public:
		OrthoCamera();

		glm::mat4 GetProjectionMatrix() const { return m_Projection; }

		// You need to call this method after updating one of the camera's parameters
		void UpdateMatrices();
		float xMin = 0.0f; float xMax = 800.0f;
		float yMin = 0.0f; float yMax = 600.0f;
		float Near = 0.01f;
		float Far = 1.0f;

	private:
		glm::mat4 m_Projection;
	};
}