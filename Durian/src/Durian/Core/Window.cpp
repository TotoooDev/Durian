#include <pch.h>
#include <Durian/Core/Window.h>
#include <Durian/Event/Events.h>
#include <SDL2/SDL_image.h>

namespace Durian
{
	bool g_IsSDLInit = false;
	unsigned int g_NumWindows = 0;

	Window::Window(const WindowSpecification& spec)
		: m_Spec(spec)
	{
		Init();
		CreateSDLWindow();
		// CreateRenderer();
		SetCallbacks();
		g_NumWindows++;
	}

	Window::~Window()
	{
		// SDL_DestroyRenderer(m_Renderer);
		SDL_DestroyWindow(m_NativeWindow);
		g_NumWindows--;
		// No more windows
		if (g_NumWindows <= 0)
		{
			IMG_Quit();
			SDL_Quit();
		}
	}

	void Window::SetVSync(bool flag)
	{
		m_Spec.VSync = flag;
		if (m_Spec.VSync)
			SDL_GL_SetSwapInterval(1);
		else
			SDL_GL_SetSwapInterval(0);
		// CreateRenderer();
	}

	// void Window::SetDrawColor(const Color& color)
	// {
	// 	SDL_SetRenderDrawColor(m_Renderer, (unsigned char)(color.r * 255), (unsigned char)(color.g * 255), (unsigned char)(color.b * 255), (unsigned char)(color.a * 255));
	// }

	// void Window::Clear(const Color& color)
	// {
	// 	SetDrawColor(color);
	// 	SDL_RenderClear(m_Renderer);
	// }

	void Window::Present()
	{
		// SDL_RenderPresent(m_Renderer);
		SDL_GL_SwapWindow(m_NativeWindow);
	}

	void Window::PollEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)); // Poll events, this is needed so SDL calls the event callback
	}

	void Window::Init()
	{
		if (!g_IsSDLInit)
		{
			if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
			{
				DURIAN_LOG_ERROR("Failed to initialize SDL!");
				DURIAN_LOG_INFO("SDL info: {0}", SDL_GetError());
				return;
			}
			if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
			{
				DURIAN_LOG_ERROR("Failed to initialize SDL_image!");
				DURIAN_LOG_INFO("IMG info: {0}", IMG_GetError());
				return;
			}
			g_IsSDLInit = true;
		}
	}

	void Window::CreateSDLWindow()
	{
		m_NativeWindow = SDL_CreateWindow(m_Spec.Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Spec.Width, m_Spec.Height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
		m_Spec.NativeWindow = m_NativeWindow;

		#if defined DURIAN_OPENGL_DEBUG
			DURIAN_LOG_WARN("OpenGL debug context created! The application may run slower.");
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
		#endif
		auto context = SDL_GL_CreateContext(m_NativeWindow);
		DURIAN_ASSERT(context, "Failed to create OpenGL context!");

		if (m_Spec.VSync)
			SDL_GL_SetSwapInterval(1); // Set VSync
	}

	// void Window::CreateRenderer()
	// {
	// 	if (m_Renderer)
	// 		SDL_DestroyRenderer(m_Renderer);
	// 
	// 	unsigned int flags = SDL_RENDERER_ACCELERATED;
	// 	if (m_Spec.VSync)
	// 		flags |= SDL_RENDERER_PRESENTVSYNC;
	// 	m_Renderer = SDL_CreateRenderer(m_NativeWindow, -1, flags);
	// 	SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND);
	// }

	void Window::SetCallbacks()
	{
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
	}
}