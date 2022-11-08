#pragma once

#include <Durian/Core/Window.h>
#include <Durian/Event/Events.h>
#include <Durian/Event/EventBus.h>

class App
{
public:
	App();

	void Run();

private:
	void OnWindowClose(Durian::WindowClosedEvent* event);

	Durian::EventBus m_EventBus;
	Durian::Window m_Window;
	bool m_IsRunning = true;
};