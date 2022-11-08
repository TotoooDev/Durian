#pragma once

#include <Durian/Core/Window.h>
#include <SDL2/SDL.h>
#include <string>

namespace Durian
{
	class Texture
	{
	public:
		Texture(Window* window, const std::string& path = "");
		~Texture();

		void LoadFromFile(const std::string& path);
		
		SDL_Texture* GetTexture() { return m_Texture; }

	private:
		SDL_Texture* m_Texture;
		Window* m_Window;
	};
}