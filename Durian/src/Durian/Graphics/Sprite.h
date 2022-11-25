#pragma once

#include <Durian/Core/Window.h>
#include <Durian/Core/Ref.h>
#include <Durian/Graphics/Texture.h>
#include <Durian/Graphics/Camera.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

namespace Durian
{
	enum class FlipState
	{
		None = SDL_FLIP_NONE,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Vertical = SDL_FLIP_VERTICAL,
		Both = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL
	};

	class Sprite
	{
	public:
		Sprite(Window* window);

		void LoadTexture(const std::string& path);
		void SetTexture(Ref<Texture> texture) { m_Texture = texture; }
		// void SetCamera(Camera* camera) { m_Camera = camera; }

		Ref<Texture> GetTexture() { return m_Texture; }

		void Draw();

		glm::vec2 Pos = glm::vec2(0.0f);
		glm::vec2 Scale = glm::vec2(16.0f);
		glm::vec2 RotationCenter = glm::vec2(0.5f);
		double Rotation = 0.0f;
		FlipState Flip = FlipState::None;

	private:
		Window* m_Window = nullptr;

		Ref<Texture> m_Texture;
		// Camera* m_Camera = nullptr;
	};
}