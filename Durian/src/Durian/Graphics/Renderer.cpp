#include <pch.h>
#include <Graphics/Renderer.h>
#include <GL/glew.h>

namespace Durian
{
	Renderer* Renderer::m_Instance = nullptr;

	Renderer::Renderer()
		: m_ShaderColor("shaders/color.vert", "shaders/color.frag"),
		  m_ShaderTexture("shaders/texture.vert", "shaders/texture.frag")
	{
		#if defined DURIAN_OPENGL_DEBUG
				InitOpenGLDebugOutput();
		#endif

		// Setup rect VAO
		std::vector<float> quadVertices =
		{
			// Pos              // Tex coords
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f
		};
		std::vector<unsigned int> quadIndices =
		{
			0, 1, 2,
			0, 2, 3
		};
		VertexLayout layout;
		layout.AddAttribute(Type::Float, 3); // Pos
		layout.AddAttribute(Type::Float, 2); // Tex coords
		m_RectVAO.SetData(quadVertices, layout);
		m_RectEBO.SetData(quadIndices);
	}

	Renderer* Renderer::Get()
	{
		if (!m_Instance)
		{
			DURIAN_ASSERT(glewInit() == GLEW_OK, glewGetErrorString(glewInit()));
			m_Instance = new Renderer;
		}
		return m_Instance;
	}

	void Renderer::Clear(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::SetCurrentCamera(const OrthoCamera& cam, const glm::mat4& view)
	{
		m_ShaderColor.Bind();
		m_ShaderColor.SetMat4(view, "uView");
		m_ShaderColor.SetMat4(cam.GetProjectionMatrix(), "uProjection");
	}

	void Renderer::DrawRectTextured(const glm::mat4& transform, Texture* texture)
	{
		DrawVerticesTextured(transform, texture, m_RectVAO, m_RectEBO);
	}

	void Renderer::DrawRectColor(const glm::mat4& transform, const glm::vec4& color)
	{
		DrawVerticesColor(transform, color, m_RectVAO, m_RectEBO);
	}

	void Renderer::DrawVerticesTextured(const glm::mat4& transform, Texture* texture, const VAO& vao, const EBO& ebo)
	{
		texture->Bind();

		m_ShaderTexture.Bind();
		m_ShaderTexture.SetMat4(transform, "uModel");
		m_ShaderTexture.SetInt(0, "uTexture");

		vao.Bind();
		ebo.Bind();

		glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, 0);
	}

	void Renderer::DrawVerticesColor(const glm::mat4& transform, const glm::vec4& color, const VAO& vao, const EBO& ebo)
	{
		m_ShaderColor.Bind();
		m_ShaderColor.SetMat4(transform, "uModel");
		m_ShaderColor.SetVec4(color, "uColor");

		vao.Bind();
		ebo.Bind();

		glDrawElements(GL_TRIANGLES, ebo.GetCount(), GL_UNSIGNED_INT, 0);
	}

	void Renderer::InitOpenGLDebugOutput()
	{
		int flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

			// Set the callback as a lambda
			// Shamelessly stolen from https://learnopengl.com/In-Practice/Debugging
			glDebugMessageCallback(
				[](GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
				{
					// Ignore non-significant error/warning codes
					if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
					return;

					std::stringstream sstream;
					sstream << message << " ";

					switch (severity)
					{
					case GL_DEBUG_SEVERITY_HIGH:         spdlog::error(sstream.str()); break;
					case GL_DEBUG_SEVERITY_MEDIUM:       spdlog::warn(sstream.str()); break;
					case GL_DEBUG_SEVERITY_LOW:          spdlog::warn(sstream.str()); break;
					case GL_DEBUG_SEVERITY_NOTIFICATION: spdlog::info(sstream.str()); break;
					}
				}, nullptr);

			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
		}
		else
		{
			DURIAN_LOG_ERROR("Unable to create a debug context!");
		}
	}
}