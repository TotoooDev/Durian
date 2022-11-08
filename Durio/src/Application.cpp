#include <Application.h>

App::App()
	: m_Window(Durian::WindowSpecification(&m_EventBus)), m_Sprite(&m_Window)
{
	m_EventBus.Subscribe(this, &App::OnWindowClose);

	m_Sprite.Pos = Durian::Math::Vec2(100.0f);
	m_Sprite.Scale = Durian::Math::Vec2(64.0f);
	m_Sprite.Rotation = 30.0f;
	m_Sprite.LoadTexture("durian.png");
}

void App::Run()
{
	while (m_IsRunning)
	{
		m_Window.PollEvents();

		m_Window.Clear(Durian::Math::Color(0.2f, 0.2f, 0.2f, 1.0f));

		// Draw epic stuff here
		m_Sprite.Draw();
		m_Sprite.Rotation++;

		m_Window.Present();
	}
}

void App::OnWindowClose(Durian::WindowClosedEvent* event)
{
	m_IsRunning = false;
}