#pragma once

#include <Durian/Event/EventBus.h>
#include <Durian/Core/Math.h>
#include <SDL2/SDL.h>
#include <string>

namespace Durian
{
	struct WindowSpecification
	{
		WindowSpecification(EventBus* bus, const std::string& title = "Durian Window", unsigned int width = 800, unsigned int height = 600, bool vsync = true)
			: Bus(bus), Title(title), Width(width), Height(height), VSync(vsync) {}

		std::string Title = "Durian Window";
		unsigned int Width = 800;
		unsigned int Height = 600;
		EventBus* Bus = nullptr;
		bool VSync = true;
		
		SDL_Window* NativeWindow = nullptr;
	};

	class Window
	{
	public:
		Window(const WindowSpecification& spec);
		~Window();

		SDL_Renderer* GetRenderer() const { return m_Renderer; }

		void SetDrawColor(const Math::Color& color);

		void Clear(const Math::Color& color);
		void Present();
		void PollEvents();

	private:
		SDL_Window* m_NativeWindow = nullptr;
		SDL_Renderer* m_Renderer = nullptr;

		WindowSpecification m_Spec;
	};
}