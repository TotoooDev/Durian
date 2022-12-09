#pragma once

#include <Durian/Core/Window.h>
#include <Durian/Core/Layer.h>
#include <Durian/Event/EventBus.h>
#include <Durian/Event/WindowEvents.h>
#include <Durian/Audio/AudioEngine.h>

#include <vector>

namespace Durian
{
	class Application
	{
	public:
		Application(const WindowSpecification& spec);
		~Application();

		// Return the instance of the application
		static Application& Get();
		void AddLayer(Layer* layer);

		// Run the main loop of the application
		void Run();
		// Close and clean the application
		void Stop();

		// void LockMouse(bool lock);

		Window GetWindow() { return m_Window; }
		WindowSpecification GetWindowSpec() { return m_Window.GetSpecification(); }
		EventBus* GetEventBus() { return m_Window.GetSpecification().Bus; }
		AudioEngine& GetAudioEngine() { return m_AudioEngine; }
		double GetTimestep() { return m_Timestep; }

	private:
		void OnWindowClosedEvent(WindowClosedEvent* event);
		void OnWindowResizedEvent(WindowResizedEvent* event);

		static Application* m_Instance;

		Window m_Window;
		std::vector<Layer*> m_Layers;

		AudioEngine m_AudioEngine;

		bool m_IsRunning = true;
		bool m_Minimized = false;
		double m_Timestep = 0.0f;
		double m_LastFrame = 0.0f;
	};
}