#pragma once

#include <Durian/Core/Window.h>
#include <Durian/Core/Math.h>
#include <Durian/Core/Ref.h>
#include <Durian/Graphics/Texture.h>
#include <SDL2/SDL.h>

namespace Durian
{
	class Sprite
	{
	public:
		Sprite(Window* window);

		void SetTexture(Ref<Texture> texture) { m_Texture = texture; }

		void Draw();

	private:
		Window* m_Window;

		Ref<Texture> m_Texture;
		SDL_Rect m_Rect = { 100, 100, 64, 64 };
	};
}