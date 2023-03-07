#include <pch.h>
#include <Durian/Graphics/Renderer.h>
#include <Durian/Core/Window.h>
#include <Durian/Event/Events.h>
#include <imgui/imgui_impl_sdl.h>

namespace Durian
{
	bool g_IsSDLInit = false;
	unsigned int g_NumWindows = 0;

	Window::Window(const WindowSpecification& spec)
		: m_Spec(spec)
	{
		Init();
		CreateSDLWindow();
		SetCallbacks();
		g_NumWindows++;
	}

	Window::~Window()
	{
		SDL_DestroyWindow(m_NativeWindow);
		g_NumWindows--;
		// No more windows
		if (g_NumWindows <= 0)
		{
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
	}

    void Window::SetContextCurrent()
    {
        SDL_GL_MakeCurrent(m_NativeWindow, m_Spec.ContextGL);
    }

	void Window::SetTitle(const std::string& title)
	{
		SDL_SetWindowTitle(m_NativeWindow, title.c_str());
	}

	void Window::Present()
	{
		SDL_GL_SwapWindow(m_NativeWindow);
	}

	void Window::PollEvents()
	{
		// Poll events, this is needed so SDL calls the event callback
		SDL_Event event;
		while (SDL_PollEvent(&event))
			ImGui_ImplSDL2_ProcessEvent(&event);
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
			// int flags = MIX_INIT_FLAC | MIX_INIT_MID | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_OPUS;
			// if (Mix_Init(flags) != flags)
			// {
			// 	DURIAN_LOG_ERROR("Failed to initialize SDL_Mixer!");
			// 	DURIAN_LOG_INFO("SDL info: {0}", Mix_GetError());
			// 	return;
			// }
			// Mix_OpenAudio(48000, AUDIO_F32SYS, 2, 2048);
			g_IsSDLInit = true;
		}
	}

	void Window::CreateSDLWindow()
	{
		m_NativeWindow = SDL_CreateWindow(m_Spec.Title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Spec.Width, m_Spec.Height, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
		m_Spec.NativeWindow = m_NativeWindow;

		#if defined DURIAN_OPENGL_DEBUG
			DURIAN_LOG_WARN("OpenGL debug context created! The application may run slower.");
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
		#endif
		SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //OpenGL core profile
    	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 3); //OpenGL 3+
    	SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 3); //OpenGL 3.3
		auto context = SDL_GL_CreateContext(m_NativeWindow);
		DURIAN_ASSERT(context, "Failed to create OpenGL context!");
		m_Spec.ContextGL = context;

		if (m_Spec.VSync)
			SDL_GL_SetSwapInterval(1); // Set VSync

		// Call Renderer::Get to init glew
		Renderer::Get();
	}

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
