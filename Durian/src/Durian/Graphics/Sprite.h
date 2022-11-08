#pragma once

#include <Durian/Core/Window.h>
#include <Durian/Core/Math.h>
#include <Durian/Core/Ref.h>
#include <Durian/Graphics/Texture.h>
#include <SDL2/SDL.h>

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

		Ref<Texture> GetTexture() { return m_Texture; }

		void Draw();

		Math::Vec2<float> Pos = Math::Vec2(0.0f);
		Math::Vec2<float> Scale = Math::Vec2(16.0f);
		Math::Vec2<float> RotationCenter = Math::Vec2(0.5f);
		double Rotation = 0.0f;
		FlipState Flip = FlipState::None;

	private:
		Window* m_Window;

		Ref<Texture> m_Texture;
	};
}