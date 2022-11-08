#include <pch.h>
#include <Durian/Core/Window.h>
#include <Durian/Event/Events.h>

namespace Durian
{
	bool g_IsSDLInit = false;
	unsigned int g_NumWindows = 0;

	Window::Window(const WindowSpecification& spec)
		: m_Spec(spec)
	{
		if (!g_IsSDLInit)
		{
			if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			{
				DURIAN_LOG_ERROR("Failed to initialize SDL!");
				DURIAN_LOG_DEBUG("SDL info: {0}", SDL_GetError());
				return;
			}
			else
				g_IsSDLInit = true;
		}

		m_NativeWindow = SDL_CreateWindow(m_Spec.Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Spec.Width, m_Spec.Height, SDL_WINDOW_SHOWN);
		m_Spec.NativeWindow = m_NativeWindow;
		unsigned int flags = SDL_RENDERER_ACCELERATED;
		if (m_Spec.VSync)
			flags |= SDL_RENDERER_PRESENTVSYNC;
		m_Renderer = SDL_CreateRenderer(m_NativeWindow, -1, flags);

		SDL_AddEventWatch([](void* userdata, SDL_Event* event)
			{
				WindowSpecification* spec = (WindowSpecification*)userdata;
				if (!spec->Bus)
					return 1;

				switch (event->type)
				{
				case SDL_QUIT:
					spec->Bus->Publish(new WindowClosedEvent);
					break;

				case SDL_WINDOWEVENT:
					switch (event->window.event)
					{
					case SDL_WINDOWEVENT_MOVED:
						if (SDL_GetWindowID(spec->NativeWindow) == event->window.windowID)
							spec->Bus->Publish(new WindowMovedEvent(event->window.data1, event->window.data1));
						break;
					case SDL_WINDOWEVENT_RESIZED:
						if (SDL_GetWindowID(spec->NativeWindow) == event->window.windowID)
							spec->Bus->Publish(new WindowResizedEvent(event->window.data1, event->window.data1));
						break;
					}
					break;

				case SDL_KEYDOWN:
					if (SDL_GetWindowID(spec->NativeWindow) == event->key.windowID)
						spec->Bus->Publish(new KeyDownEvent(event->key.keysym.scancode));
					break;
				case SDL_KEYUP:
					if (SDL_GetWindowID(spec->NativeWindow) == event->key.windowID)
						spec->Bus->Publish(new KeyUpEvent(event->key.keysym.scancode));
					break;

				case SDL_MOUSEMOTION:
					if (SDL_GetWindowID(spec->NativeWindow) == event->motion.windowID)
						spec->Bus->Publish(new MouseMovedEvent(event->motion.x, event->motion.y));
					break;
				case SDL_MOUSEWHEEL:
					if (SDL_GetWindowID(spec->NativeWindow) == event->wheel.windowID)
						spec->Bus->Publish(new MouseScrolledEvent(event->wheel.preciseX, event->wheel.preciseY));
					break;
				case SDL_MOUSEBUTTONDOWN:
					if (SDL_GetWindowID(spec->NativeWindow) == event->button.windowID)
						spec->Bus->Publish(new MouseButtonDownEvent(event->button.button));
					break;
				case SDL_MOUSEBUTTONUP:
					if (SDL_GetWindowID(spec->NativeWindow) == event->button.windowID)
						spec->Bus->Publish(new MouseButtonUpEvent(event->button.button));
					break;

				default:
					break;
				}

				return 0;
			}, &m_Spec);

		g_NumWindows++;
	}

	Window::~Window()
	{
		SDL_DestroyRenderer(m_Renderer);
		SDL_DestroyWindow(m_NativeWindow);
		g_NumWindows--;
		// No more windows
		if (g_NumWindows <= 0)
			SDL_Quit();
	}

	void Window::Clear(float r, float g, float b)
	{
		SDL_SetRenderDrawColor(m_Renderer, (unsigned char)(r * 255), (unsigned char)(g * 255), (unsigned char)(b * 255), 255);
		SDL_RenderClear(m_Renderer);
	}

	void Window::Present()
	{
		SDL_RenderPresent(m_Renderer);
	}

	void Window::PollEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)); // Poll events, this is needed so SDL calls the event callback
	}
}