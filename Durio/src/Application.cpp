#include <Application.h>
#include <Durian/Core/Log.h>
#include <Durian/Graphics/Renderer.h>

App::App()
	: m_Window(Durian::WindowSpecification(&m_EventBus)), m_Sprite(&m_Window)
{
	m_EventBus.Subscribe(this, &App::OnWindowClose);
	m_EventBus.Subscribe(this, &App::OnKeyDown);
	m_EventBus.Subscribe(this, &App::OnKeyUp);

	m_Sprite.Pos = glm::vec2(100.0f);
	m_Sprite.Scale = glm::vec2(64.0f);
	m_Sprite.Rotation = 30.0f;
	m_Sprite.LoadTexture("img.png");
	m_Sprite.SetCamera(&m_Cam);

	// Durian::Renderer::Get();
}

void App::Run()
{
	while (m_IsRunning)
	{
		m_Window.PollEvents();

		// m_Window.Clear(Durian::Color(0.2f, 0.2f, 0.2f, 1.0f));
		Durian::Renderer::Get()->Clear(0.2f, 0.2f, 0.2f);

		// Draw epic stuff here

		if (Movement.Right)
			m_Cam.Pos.x++;
		if (Movement.Left)
			m_Cam.Pos.x--;
		if (Movement.Up)
			m_Cam.Distance-=0.1f;
		if (Movement.Down)
			m_Cam.Distance+=0.1f;

		m_Sprite.Draw();
		m_Sprite.Rotation++;

		m_Window.Present();
	}
}

void App::OnWindowClose(Durian::WindowClosedEvent* event)
{
	m_IsRunning = false;
}

void App::OnKeyDown(Durian::KeyDownEvent* event)
{
	switch (event->Keycode)
	{
	case DURIAN_SCANCODE_RIGHT:
		Movement.Right = true;
		break;

	case DURIAN_SCANCODE_LEFT:
		Movement.Left = true;
		break;

	case DURIAN_SCANCODE_UP:
		Movement.Up = true;
		break;

	case DURIAN_SCANCODE_DOWN:
		Movement.Down = true;
		break;

	default:
		break;
	}
}

void App::OnKeyUp(Durian::KeyUpEvent* event)
{
	switch (event->Keycode)
	{
	case DURIAN_SCANCODE_RIGHT:
		Movement.Right = false;
		break;

	case DURIAN_SCANCODE_LEFT:
		Movement.Left = false;
		break;

	case DURIAN_SCANCODE_UP:
		Movement.Up = false;
		break;

	case DURIAN_SCANCODE_DOWN:
		Movement.Down = false;
		break;

	default:
		break;
	}
}