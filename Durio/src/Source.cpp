#include <Durian/Core/Application.h>
#include <Durian/Core/Window.h>
#include <Durian/Core/Ref.h>
#include <Durian/Audio/SoundPool.h>
#include <Durian/Event/Events.h>
#include <Durian/Event/EventBus.h>
#include <Durian/Graphics/Texture.h>
#include <Durian/Graphics/Renderer.h>
#include <Durian/Scene/Scene.h>
#include <Durian/Scene/Entity.h>
#include <Durian/Scene/Components.h>

class CustomLayer : public Durian::Layer
{
public:
	virtual void OnCreate() override
	{
		m_SpriteEntity = m_Scene.CreateEntity("Sprite");
		// auto& transformComp = m_SpriteEntity.AddComponent<Durian::TransformComponent>();
		// transformComp.Scale = glm::vec3(64.0f, 64.0f, 64.0f);
		// auto& texComp = m_SpriteEntity.AddComponent<Durian::SpriteComponent>(Durian::CreateRef<Durian::Texture>("img.png"));
		m_SpriteEntity.AddComponent<Durian::ScriptComponent>(m_SpriteEntity, "Script.lua");
		// auto& emitterComp = m_SpriteEntity.AddComponent<Durian::SoundEmitterComponent>();
		// Durian::Ref<Durian::Sound> sound = Durian::CreateRef<Durian::Sound>("baow.mp3");
		// Durian::Application::Get().GetSoundPool().AddSound(sound);
		// emitterComp.SoundQueue.push(sound);

		m_CameraEntity = m_Scene.CreateEntity("Camera");
		m_CameraEntity.AddComponent<Durian::TransformComponent>();
		Durian::OrthoCamera cam;
		m_CameraEntity.AddComponent<Durian::OrthoCameraComponent>(cam);
		m_CameraEntity.AddComponent<Durian::SoundListenerComponent>();
	}

	virtual void OnUpdate(double timestep) override
	{
		Durian::Renderer::Get()->Clear(0.2f, 0.2f, 0.2f);
		m_Scene.UpdateScene(timestep);
	}

private:
	Durian::Scene m_Scene;
	Durian::Entity m_SpriteEntity;
	Durian::Entity m_CameraEntity;
};

int main(int argc, char* argv[])
{
	Durian::EventBus bus;
	Durian::WindowSpecification spec(&bus, "Durian Window");
	Durian::Application* app = new Durian::Application(spec);
	app->AddLayer(new CustomLayer());

	app->Run();

	return 0;
}