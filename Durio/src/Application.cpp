#include <Application.h>

App::App()
	: m_Window(Durian::WindowSpecification(&m_EventBus))
{
	m_EventBus.Subscribe(this, &App::OnWindowClose);
}

void App::Run()
{
	while (m_IsRunning)
	{
		m_Window.PollEvents();

		m_Window.Clear();

		// Draw epic stuff here

		m_Window.Present();
	}
}

void App::OnWindowClose(Durian::WindowClosedEvent* event)
{
	m_IsRunning = false;
}