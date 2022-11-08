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
	void OnKeyDown(Durian::KeyDownEvent* event);
	void OnKeyUp(Durian::KeyUpEvent* event);

	struct
	{
		bool Right = false, Left = false, Up = false, Down = false;
	}  Movement;

	Durian::EventBus m_EventBus;
	Durian::Window m_Window;
	Durian::Sprite m_Sprite;
	Durian::Camera m_Cam;
	bool m_IsRunning = true;
};