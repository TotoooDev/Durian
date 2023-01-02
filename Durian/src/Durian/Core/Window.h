#pragma once

#include <Durian/Event/EventBus.h>
#include <SDL2/SDL.h>
#include <string>

namespace Durian
{
	struct WindowSpecification
	{
		WindowSpecification(EventBus* bus, const std::string& title = "Durian Window", unsigned int width = 1280, unsigned int height = 720, bool vsync = true)
			: Bus(bus), Title(title), Width(width), Height(height), VSync(vsync) {}

		std::string Title;
		unsigned int Width;
		unsigned int Height;
		EventBus* Bus = nullptr;
		bool VSync;
		
		SDL_Window* NativeWindow = nullptr;
		SDL_GLContext ContextGL = nullptr;
	};

	class Window
	{
	public:
		Window(const WindowSpecification& spec);
		~Window();

		WindowSpecification GetSpecification() const { return m_Spec; }

		void SetVSync(bool flag);
        void SetContextCurrent();

		void Present();
		void PollEvents();

	private:
		void Init();
		void CreateSDLWindow();
		void SetCallbacks();

		SDL_Window* m_NativeWindow = nullptr;

		WindowSpecification m_Spec;
	};
}
