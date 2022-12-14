#include <Durian/Core/Application.h>
#include <Durian/Core/Window.h>
#include <EditorLayer.h>

int main(int argc, char* argv[])
{
	Durian::EventBus bus;
	Durian::WindowSpecification spec(&bus, "Durian Window");
	Durian::Application* app = new Durian::Application(spec);
	app->AddLayer(new Durian::EditorLayer());

	app->Run();

	return 0;
}