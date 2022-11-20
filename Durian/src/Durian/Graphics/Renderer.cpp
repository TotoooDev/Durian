#include <pch.h>
#include <Graphics/Renderer.h>
#include <GL/glew.h>

namespace Durian
{
	Renderer* Renderer::m_Instance = nullptr;

	Renderer* Renderer::Get()
	{
		if (!m_Instance)
		{
			m_Instance = new Renderer;
			DURIAN_ASSERT(glewInit() == GLEW_OK, glewGetErrorString(glewInit()));
			#if defined DURIAN_OPENGL_DEBUG
				InitOpenGLDebugOutput();
			#endif
		}
		return m_Instance;
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