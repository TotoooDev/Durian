#pragma once

namespace Durian
{
	class Renderer
	{
	public:
		static Renderer* Get();

		// void DrawRectTextured();
		// void DrawRectColor();

	private:
		Renderer() = default;

		static void InitOpenGLDebugOutput();

		static Renderer* m_Instance;
	};
}