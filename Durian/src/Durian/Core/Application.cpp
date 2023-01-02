#include <pch.h>
#include <Durian/Core/Application.h>
#include <Durian/Core/Window.h>
#include <Durian/Event/WindowEvents.h>
#include <Durian/Graphics/Renderer.h>

// #include <ImGui/imgui.h>
// #include <ImGui/imgui_impl_glfw.h>
// #include <ImGui/imgui_impl_opengl3.h>

namespace Durian
{
	Application* Application::m_Instance = nullptr;

	Application::Application(const WindowSpecification& data)
		: m_Window(data)
	{
		if (m_Instance == nullptr)
		{
			m_Instance = this;
		}
		else
		{
			spdlog::error("An application already exists!");
		}

		// spdlog setup
		auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		consoleSink->set_pattern("[%D %T] [%^%l%$] %v");
		auto fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>("logs/TOE_Logs.log", 1048576 * 5, 3);
		fileSink->set_pattern("[%D %T] [%^%l%$] %v");
		spdlog::logger logger("Default Logger", { consoleSink, fileSink });
		spdlog::set_default_logger(std::make_shared<spdlog::logger>(logger));

		m_ImGuiLayer = new ImGuiLayer;
		m_ImGuiLayer->OnCreate();

		// Sub to the window events
		m_Window.GetSpecification().Bus->Subscribe(this, &Application::OnWindowClosedEvent);
		m_Window.GetSpecification().Bus->Subscribe(this, &Application::OnWindowResizedEvent);
	}

	Application::~Application()
	{

	}

	Application& Application::Get()
	{
		return *m_Instance;
	}

	void Application::AddLayer(Layer* layer)
	{
		m_Layers.push_back(layer);
		layer->OnCreate();
	}

	void Application::Run()
	{
		while (m_IsRunning)
		{
			m_Window.PollEvents();

			if (!m_Minimized)
			{
				// Update all layers
				for (auto& layer : m_Layers)
				{
					layer->OnUpdate(m_Timestep);
				}
			}

			#ifdef DURIAN_DEBUG
				m_AudioEngine.PrintErrors();
			#endif

			// ImGui
			m_ImGuiLayer->Begin();
			for (auto& layer : m_Layers)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window.Present();

			// Update timestep
			double currentFrame = (double)SDL_GetTicks() * 0.001f;
			m_Timestep = currentFrame - m_LastFrame;
			m_LastFrame = currentFrame;
		}
	}

	void Application::Stop()
	{
		m_IsRunning = false;
	}

	void Application::OnWindowClosedEvent(WindowClosedEvent* event)
	{
		Stop();
	}
	void Application::OnWindowResizedEvent(WindowResizedEvent* event)
	{
		if (event->Width == 0 && event->Height == 0)
			m_Minimized = true;
		else
			m_Minimized = false;
		glViewport(0, 0, m_Window.GetSpecification().Width, m_Window.GetSpecification().Height);
	}
}