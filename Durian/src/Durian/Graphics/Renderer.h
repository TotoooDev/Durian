#pragma once
#include <Durian/Graphics/Texture.h>
#include <glm/glm.hpp>

namespace Durian
{
	class Renderer
	{
	public:
		static Renderer* Get();

		void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

		void DrawRectTextured(glm::vec2 pos, glm::vec2 scale, Texture* texture);
		// void DrawRectColor();

	private:
		Renderer() = default;

		static void InitOpenGLDebugOutput();

		static Renderer* m_Instance;
	};
}