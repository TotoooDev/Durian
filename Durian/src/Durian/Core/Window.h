#pragma once

#include <Durian/Event/EventBus.h>
#include <SDL2/SDL.h>
#include <string>

namespace Durian
{
	struct WindowSpecification
	{
		std::string Title = "Durian Window";
		unsigned int Width = 800;
		unsigned int Height = 600;
		bool VSync = true;

		EventBus* Bus = nullptr;
		SDL_Window* NativeWindow = nullptr;
	};

	class Window
	{
	public:
		Window(const WindowSpecification& spec);
		~Window();

		void PollEvents();

	private:
		SDL_Window* m_NativeWindow = nullptr;
		SDL_Renderer* m_Renderer = nullptr;

		WindowSpecification m_Spec;
	};
}