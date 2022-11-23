#pragma once
#include <glm/glm.hpp>

namespace Durian
{
	class Camera
	{
	public:
		glm::vec2 Pos = glm::vec2(0.0f);
		float Distance = 1.0f;
	};
}