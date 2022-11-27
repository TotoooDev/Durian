#include <Application.h>
#include <Durian/Core/Log.h>
#include <Durian/Core/Ref.h>
#include <Durian/Graphics/Renderer.h>
#include <Durian/Scene/Components.h>

App::App()
	: m_Window(Durian::WindowSpecification(&m_EventBus))// , m_Sprite(&m_Window)
{
	m_EventBus.Subscribe(this, &App::OnWindowClose);
	m_EventBus.Subscribe(this, &App::OnKeyDown);
	m_EventBus.Subscribe(this, &App::OnKeyUp);

	m_SpriteEntity = m_Scene.CreateEntity("Sprite");
	// auto& transformComp = m_SpriteEntity.AddComponent<Durian::TransformComponent>();
	// transformComp.Scale = glm::vec3(64.0f, 64.0f, 64.0f);
	auto& texComp = m_SpriteEntity.AddComponent<Durian::SpriteComponent>(Durian::CreateRef<Durian::Texture>("img.png"));
	m_SpriteEntity.AddComponent<Durian::ScriptComponent>(m_SpriteEntity, "Script.lua");

	m_CameraEntity = m_Scene.CreateEntity("Camera");
	m_CameraEntity.AddComponent<Durian::TransformComponent>();
	Durian::OrthoCamera cam;
	m_CameraEntity.AddComponent<Durian::OrthoCameraComponent>(cam);
}

void App::Run()
{
	while (m_IsRunning)
	{
		m_Window.PollEvents();

		// m_Window.Clear(Durian::Color(0.2f, 0.2f, 0.2f, 1.0f));
		Durian::Renderer::Get()->Clear(0.2f, 0.2f, 0.2f);

		// Draw epic stuff here
		m_Scene.UpdateScene(0.0f);

		// if (Movement.Right)
		// 	m_Cam.Pos.x++;
		// if (Movement.Left)
		// 	m_Cam.Pos.x--;
		// if (Movement.Up)
		// 	m_Cam.Distance-=0.1f;
		// if (Movement.Down)
		// 	m_Cam.Distance+=0.1f;

		// m_Sprite.Draw();
		// m_Sprite.Rotation++;

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