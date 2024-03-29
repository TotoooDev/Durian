#pragma once
#include <Durian/Core/Ref.h>
#include <Durian/Core/Timer.h>
#include <Durian/Graphics/Shader.h>
#include <Durian/Graphics/Texture.h>
#include <Durian/Graphics/VertexObjects.h>
#include <Durian/Graphics/Camera.h>
#include <Durian/Graphics/Framebuffer.h>
#include <glm/glm.hpp>

namespace Durian
{
	struct RendererStats
	{
		unsigned int NumVertices = 0;
		unsigned int NumIndices = 0;
		float FrameTime = 0.0f;
	};

	class Renderer
	{
	public:
		static Renderer* Get();
		static RendererStats GetRendererStats() { return m_Stats; }

		void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
		void SetCurrentCamera(const OrthoCamera& cam, const glm::mat4& view);

		void DrawRectTextured(const glm::mat4& transform, Ref<Texture> texture);
		void DrawRectColor(const glm::mat4& transform, const glm::vec4& color);

		void DrawVerticesTextured(const glm::mat4& transform, Ref<Texture> texture, const VAO& vao, const EBO& ebo);
		void DrawVerticesColor(const glm::mat4& transform, const glm::vec4& color, const VAO& vao, const EBO& ebo);

	private:
		Renderer();
		static void InitOpenGLDebugOutput();

		static Renderer* m_Instance;

		Ref<Framebuffer> m_FramebufferTarget;

		Shader m_ShaderColor;
		Shader m_ShaderTexture;
		
		VAO m_RectVAO;
		EBO m_RectEBO;

		static RendererStats m_Stats;
		#ifdef DURIAN_DEBUG
			Timer m_Timer;
		#endif
	};
}