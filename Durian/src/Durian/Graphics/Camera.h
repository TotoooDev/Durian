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
		float xMin = -400; float xMax = 400;
		float yMin = 300; float yMax = -300;
		float Near = -1;
		float Far = 1;

	private:
		glm::mat4 m_Projection;
	};
}