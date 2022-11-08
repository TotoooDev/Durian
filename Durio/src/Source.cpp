#include <Durian/Core/Window.h>
#include <Durian/Event/EventBus.h>
#include <Durian/Event/Events.h>
#include <iostream>

struct App
{
	App()
		: Window({ "a", 800, 600, true, &Bus })
	{
		Bus.Subscribe(this, &App::Quit);
		Bus.Subscribe(this, &App::KeyDown);
	}

	void Run()
	{
		while (IsRunning)
		{
			Window.PollEvents();
		}
	}

	void Quit(Durian::WindowClosedEvent* event)
	{
		IsRunning = false;
	}

	void KeyDown(Durian::KeyDownEvent* event)
	{
		std::cout << event->Keycode << std::endl;
	}

	Durian::EventBus Bus;
	Durian::Window Window;
	bool IsRunning = true;
};

int main(int argc, char* argv[])
{
	App app;
	app.Run();

	return 0;
}