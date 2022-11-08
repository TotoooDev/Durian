#pragma once

#include <Durian/Core/Window.h>
#include <Durian/Event/Events.h>
#include <Durian/Event/EventBus.h>
#include <Durian/Graphics/Sprite.h>

class App
{
public:
	App();

	void Run();

private:
	void OnWindowClose(Durian::WindowClosedEvent* event);

	Durian::EventBus m_EventBus;
	Durian::Window m_Window;
	Durian::Sprite m_Sprite;
	Durian::Texture m_Texture;
	bool m_IsRunning = true;
};